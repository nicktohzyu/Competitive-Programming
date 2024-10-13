
#include <format>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

enum class Side {
    Buy, Sell
};

struct Order {
    const Side side;
    const int id;
    const int price;
    int visible_quantity;
    int hidden_quantity;
    const int max_peak_size;

    bool isAlive() const {
        return visible_quantity > 0 || hidden_quantity > 0;
    }
};

// To track which level an order is in (for efficient cancelling)
struct OrderLocation {
    Side side;
    int price;
};

class PriceLevel {
public:
    const int price;
    const Side side;

private:
    std::list<Order> orders; // Implicitly arranged by time priority
    // Invariant that orders in `orders` must have non-zero visible quantity
    // Invariant that order in `orders` corresponds to an entry in `order_it_by_id`
    // and in MatchingEngine's `order_location_by_id`

    // For efficient cancelling
    std::unordered_map<int, std::list<Order>::iterator> order_it_by_id;
    /* An alternative to this approach could be lazy delete, where we simply store
     * the id in a hashset on cancellation and only remove the order when we come
     * across it later. In a practical matching engine it might cause an accumulation
     * of a lot of dead orders in levels that aren't traded against.
     * Technically for this assignment we'll always hit it when printing the
     * book, but I didn't want to have logic triggered by the IO routines. */

public:
    PriceLevel(int p, Side s) :
            price{p}, side{s}, orders{} {}

    void addOrder(const Order &order) {
        orders.emplace_back(order);
        order_it_by_id[order.id] = std::prev(orders.end());
    }

    /* To work with this implementation for fast cancelling (where we need to cleanup our id maps
     * when a resting order is filled) I considered the alternatives of passing
     * `order_location_by_id` ref against
     * - initialize the PriceLevel class with std::function captured lambda
     *      performance hit due to un-inlineable function with type erasure and this/reference
     *      capture. We could template over the lambda type instead of using std::function
     *      to mitigate this performance hit but I felt it was unnecessarily complex
     * - initialize the PriceLevel class with ref to PriceLevel
     *      unnecessary coupling and less clear code
     */
    void matchAgainstIncomingOrder(Order &incoming_order,
                                   std::unordered_map<int, OrderLocation> &order_location_by_id) {
        // Resting_order_id -> total traded quantity
        std::unordered_map<int, int> trade_total_quantities;
        // Sequence of resting order_ids that were traded against
        std::vector<int> trade_sequence;

        auto order_it = orders.begin();
        while (order_it != orders.end() && incoming_order.isAlive()) {
            Order &resting_order = *order_it;

            // Determine trade quantity
            int matched_quantity = std::min(incoming_order.visible_quantity,
                                            resting_order.visible_quantity);

            // Update incoming order and resting order
            incoming_order.visible_quantity -= matched_quantity;
            resting_order.visible_quantity -= matched_quantity;

            auto [trade_it, inserted] = trade_total_quantities.try_emplace(resting_order.id, 0);
            trade_it->second += matched_quantity;
            if (inserted) {
                trade_sequence.push_back(resting_order.id);
            }

            if (resting_order.visible_quantity > 0) {
                // Aggressing order is fully filled
                break;
            }
            // Now resting_order.visible_quantity == 0

            if (resting_order.hidden_quantity > 0) {
                // Refill iceberg
                Order refilled{resting_order};
                int replenish_qty = std::min(refilled.hidden_quantity, refilled.max_peak_size);
                refilled.visible_quantity = replenish_qty;
                refilled.hidden_quantity -= replenish_qty;
                addOrder(refilled);
            } else {
                // Order is fully filled
                order_it_by_id.erase(resting_order.id);
                order_location_by_id.erase(resting_order.id);
            }

            // Either this order is fully filled or we've refilled it (and pushed a copy)
            // In either case we remove it from the front of the list
            order_it = orders.erase(order_it);
        }

        // Generate Trade messages
        for (auto resting_id: trade_sequence) {
            int trade_qty = trade_total_quantities[resting_id];
            std::cout << std::format(
                    "M {} {} {} {}\n",
                    incoming_order.side == Side::Buy ? incoming_order.id : resting_id /* buyer ID */,
                    incoming_order.side == Side::Sell ? incoming_order.id : resting_id /* seller ID */,
                    price /* trade at resting price (this level) */,
                    trade_qty);
        }
    }

    void printBook() const {
        for (const auto &order: orders) {
            std::cout << std::format("O {} {} {} {}\n",
                                     side == Side::Buy ? "B" : "S",
                                     order.id,
                                     order.price,
                                     order.visible_quantity);
        }
    }

    bool empty() const {
        return orders.empty();
    }

    void cancelOrder(int id) {
        auto map_it = order_it_by_id.find(id);
        orders.erase(map_it->second);
        order_it_by_id.erase(map_it);
    }
};

// Constrains templating to reduce buy/sell code duplication
template<typename T>
concept BookSide =
std::is_same_v<T, std::map<int, PriceLevel, std::less<>>> ||
std::is_same_v<T, std::map<int, PriceLevel, std::greater<>>>;

class MatchingEngine {
private:
    std::map<int, PriceLevel, std::greater<>> buy_levels;
    std::map<int, PriceLevel, std::less<>> sell_levels;
    /* We could cache the top of book iterator for a constant factor improvement
     * but I chose not to for simplicity, assuming the number of levels would be
     * relatively small compared to order volume and the TOB might often shift
     *
     * An alternative implementation to having price levels could be to store all orders
     * on the same side in a single set. I'd enhance orders with a sequentially generated
     * seqno and provide custom comparators for buy/sell. However, this approach is
     * asymptotically slower and less extensible. */

    // Map from order ID to its location
    std::unordered_map<int, OrderLocation> order_location_by_id;

public:
    MatchingEngine() : buy_levels(), sell_levels(), order_location_by_id() {}

    void insertLimitOrder(Side side, int id, int price, int quantity) {
        // Handle limit orders as iceberg with quantity = peak size
        insertIcebergOrder(side, id, price, quantity, quantity);
    }

    void insertIcebergOrder(Side side, int id, int price, int quantity, int peak_size) {
        // When an order is aggressing, its full quantity is available
        Order incoming_order{side, id, price, quantity, 0, peak_size};
        matchOrder(incoming_order);

        // If there is remaining quantity, hide the non-peak amount
        // Per specification, visible peak size is determined after trades effected
        if (incoming_order.isAlive()) {
            if (incoming_order.visible_quantity > peak_size) {
                incoming_order.hidden_quantity =
                        incoming_order.visible_quantity - peak_size;
                incoming_order.visible_quantity = peak_size;
            }
            enterOrderIntoBook(incoming_order);
        }
        printOrderBook();
    }

    void cancelOrder(int id) {
        // Per spec, assume that order is live
        auto it = order_location_by_id.find(id);
        auto [side, price] = it->second;

        auto cancelInBookSide = [price, id](BookSide auto &book_side) -> void {
            auto price_level_it = book_side.find(price);
            PriceLevel &level = price_level_it->second;
            level.cancelOrder(id);
            if (level.empty()) {
                book_side.erase(price_level_it);
            }
        };

        if (side == Side::Buy) {
            cancelInBookSide(buy_levels);
        } else {
            cancelInBookSide(sell_levels);
        }

        order_location_by_id.erase(it);
        printOrderBook();
    }

    void printOrderBook() const {
        for (const auto &[_, price_level]: buy_levels) {
            price_level.printBook();
        }
        for (const auto &[_, price_level]: sell_levels) {
            price_level.printBook();
        }
        std::cout << std::endl;
    }

private:
    void enterOrderIntoBook(const Order &order) {
        // Implicitly template over map comparator type
        auto insertIntoBookSide = [&, this](BookSide auto &book_side) -> void {
            auto [price_level_it, inserted] =
                    book_side.try_emplace(order.price, order.price, order.side);
            // Map the order ID to its level for fast cancellation
            order_location_by_id[order.id] = OrderLocation{.side = order.side,
                                                           .price = order.price};
            PriceLevel &level = price_level_it->second;
            level.addOrder(order);
        };

        if (order.side == Side::Buy) {
            insertIntoBookSide(buy_levels);
        } else {
            insertIntoBookSide(sell_levels);
        }
    }

    void matchOrder(Order &incoming_order) {
        auto matchOrders = [&](BookSide auto &book_side) -> void {
            auto top_level_it = book_side.begin();
            while (top_level_it != book_side.end() && incoming_order.isAlive()) {
                /* Explicit type hint to aid codesense - seems like the concept constraint isn't sufficient */
                PriceLevel &top_level = top_level_it->second;
                if (book_side.key_comp()(incoming_order.price, top_level.price)) {
                    // Prices do not intersect
                    break;
                }
                // Matching may result in resting orders being cleared,
                // we want to remove them from the `order_location_by_id` map
                top_level.matchAgainstIncomingOrder(incoming_order, order_location_by_id);

                if (!top_level.empty()) {
                    // If the level isn't cleared then the aggressor must be fully filled
                    break;
                }
                // Otherwise, remove the empty "top of book" and advance to new TOB
                top_level_it = book_side.erase(top_level_it);
            }
        };
        if (incoming_order.side == Side::Buy) {
            matchOrders(sell_levels);
        } else {
            matchOrders(buy_levels);
        }
    }
};

int main() {
    MatchingEngine engine;
    std::string line;
    while (getline(std::cin, line)) {
        // Ignore empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        char cmd;
        ss >> cmd;

        if (cmd == 'L') {
            // Insert Limit Order
            char side_char;
            int id, price, quantity;
            ss >> side_char >> id >> price >> quantity;
            Side side = (side_char == 'B') ? Side::Buy : Side::Sell;
            engine.insertLimitOrder(side, id, price, quantity);
        } else if (cmd == 'I') {
            // Insert Iceberg Order
            char side_char;
            int id, price, quantity, peak_size;
            ss >> side_char >> id >> price >> quantity >> peak_size;
            Side side = (side_char == 'B') ? Side::Buy : Side::Sell;
            engine.insertIcebergOrder(side, id, price, quantity, peak_size);
        } else if (cmd == 'C') {
            // Cancel Order
            int id;
            ss >> id;
            engine.cancelOrder(id);
        }
    }
}
