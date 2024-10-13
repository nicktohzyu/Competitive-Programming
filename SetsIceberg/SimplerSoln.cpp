#include <bits/stdc++.h>

using namespace std;

enum class Side {
    Buy, Sell
};

struct Order {
    const int id;
    const Side side;
    const int price;
    int visibleQuantity;
    int hiddenQuantity;
    const int maxPeakSize;
    size_t time; // For ordering

    Order(int _id, Side _side, int _price, int _quantity, int _peakSize, size_t _time)
            : id(_id), side(_side), price(_price), visibleQuantity(min(_quantity, _peakSize)),
              hiddenQuantity(_quantity - min(_quantity, _peakSize)),
              maxPeakSize(_peakSize), time(_time) {}

    bool isAlive() const {
        return visibleQuantity > 0 || hiddenQuantity > 0;
    }
};

struct TradeMessage {
    const int buyId;
    const int sellId;
    const Side side;
    int quantity;
};

struct BuyComparator {
    bool operator()(const Order &a, const Order &b) const {
        if (a.price != b.price)
            return a.price > b.price;
        return a.time < b.time;
    }
};

struct SellComparator {
    bool operator()(const Order &a, const Order &b) const {
        if (a.price != b.price)
            return a.price < b.price;
        return a.time < b.time;
    }
};

class MatchingEngine {
private:
    set<Order, BuyComparator> buyBook;
    set<Order, SellComparator> sellBook;
    unordered_map<int, set<Order, BuyComparator>::iterator> buyMap;
    unordered_map<int, set<Order, SellComparator>::iterator> sellMap;
    size_t timeCounter = 0;

public:
    void insertOrder(Side side, int id, int price, int quantity, int peakSize) {
        Order incoming(id, side, price, quantity, peakSize, timeCounter++);
        // Determine opposite book
        if (side == Side::Buy) {
            matchOrder(incoming, sellBook, sellMap);
            if (incoming.isAlive()) {
                auto [it, _] = buyBook.insert(incoming);
                buyMap[id] = it;
            }
        } else {
            matchOrder(incoming, buyBook, buyMap);
            if (incoming.isAlive()) {
                auto [it, _] = sellBook.insert(incoming);
                sellMap[id] = it;
            }
        }
        printOrderBook();
    }

    void cancelOrder(int id) {
        if (buyMap.find(id) != buyMap.end()) {
            buyBook.erase(buyMap[id]);
            buyMap.erase(id);
        } else if (sellMap.find(id) != sellMap.end()) {
            sellBook.erase(sellMap[id]);
            sellMap.erase(id);
        }
        printOrderBook();
    }

private:
    template <typename Cmp>
    void matchOrder(Order &incomingOrder, set<Order, Cmp> &oppositeBook,
                    unordered_map<int, typename set<Order, Cmp>::iterator> &oppositeMap) {
        unordered_map<int, int> matchedTradeQuantities; // resting order_id -> quantity traded
        vector<int> matchedOrderIDs; // preserve trade order

        auto restingOrderIt = oppositeBook.begin();

        while (restingOrderIt != oppositeBook.end() && incomingOrder.visibleQuantity > 0) {
            if (incomingOrder.side == Side::Buy) {
                if (restingOrderIt->price > incomingOrder.price)
                    break;
            } else {
                if (restingOrderIt->price < incomingOrder.price)
                    break;
            }

            int tradeQuantity = min(incomingOrder.visibleQuantity, restingOrderIt->visibleQuantity);

            // For outputting trade report later
            /* Can be done more efficiently with try_emplace, but I thought this is easier to read */
            if (matchedTradeQuantities.contains(restingOrderIt->id)) {
                // May re-match an iceberg
                matchedTradeQuantities[restingOrderIt->id] += tradeQuantity;
            } else {
                matchedTradeQuantities[restingOrderIt->id] = tradeQuantity;
                matchedOrderIDs.push_back(restingOrderIt->id);
            }

            // Update quantities
            Order resting = *restingOrderIt;
            auto current_id = restingOrderIt->id;
            oppositeBook.erase(restingOrderIt);
            auto map_it = oppositeMap.find(current_id);
            if (map_it != oppositeMap.end())
                oppositeMap.erase(map_it);

            resting.visibleQuantity -= tradeQuantity;
            incomingOrder.visibleQuantity -= tradeQuantity;

            if (resting.visibleQuantity == 0 && resting.hiddenQuantity > 0) {
                // Refill the peak
                int refillQty = min(resting.hiddenQuantity, resting.maxPeakSize);
                resting.visibleQuantity = refillQty;
                resting.hiddenQuantity -= refillQty;
                resting.time = timeCounter++;
                oppositeBook.insert(resting);
                auto new_it = oppositeBook.find(resting);
                oppositeMap[resting.id] = new_it;
            }

            if (resting.visibleQuantity > 0) {
                // Reinsert the order if not fully filled
                oppositeBook.insert(resting);
                auto new_it = oppositeBook.find(resting);
                oppositeMap[resting.id] = new_it;
            }

            restingOrderIt = oppositeBook.begin(); // Restart iteration as the set might have been modified
        }

        // Emit trade messages
        for (const auto &[order_id, qty_pair]: tradeMap) {
            if (incomingOrder.side == Side::Buy) {
                cout << "M " << qty_pair.first << " " << order_id << " "
                     << (incomingOrder.side == Side::Buy ? incomingOrder.price : incomingOrder.price) << " "
                     << qty_pair.second << "\n";
            } else {
                cout << "M " << order_id << " " << qty_pair.first << " "
                     << (incomingOrder.side == Side::Buy ? incomingOrder.price : incomingOrder.price) << " "
                     << qty_pair.second << "\n";
            }
        }
    }

    void printOrderBook() {
        // Collect buy orders
        vector<Order> buys;
        for (const auto &order: buyBook) {
            buys.push_back(order);
        }

        // Collect sell orders
        vector<Order> sells;
        for (const auto &order: sellBook) {
            sells.push_back(order);
        }

        // Print buy orders
        for (const auto &order: buys) {
            cout << "O " << (order.side == Side::Buy ? "B" : "S") << " " << order.id << " " << order.price << " "
                 << order.visibleQuantity << "\n";
        }

        // Print sell orders
        for (const auto &order: sells) {
            cout << "O " << (order.side == Side::Buy ? "B" : "S") << " " << order.id << " " << order.price << " "
                 << order.visibleQuantity << "\n";
        }

        cout << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    MatchingEngine engine;
    string line;
    while (getline(cin, line)) {
        // Trim the line
        string trimmed = line;
        trimmed.erase(remove(trimmed.begin(), trimmed.end(), '\r'), trimmed.end());

        // Skip empty lines or comments
        if (trimmed.empty() || trimmed[0] == '#')
            continue;

        // Tokenize the line
        stringstream ss(trimmed);
        vector<string> tokens;
        string token;
        while (ss >> token)
            tokens.push_back(token);

        if (tokens.empty())
            continue;

        char type = tokens[0][0];
        if (type == 'L' || type == 'I') {
            // Insert Limit or Iceberg Order
            if (type == 'L' && tokens.size() == 5) {
                // Limit Order
                char side_char = tokens[1][0];
                Side side = (side_char == 'B') ? Side::Buy : Side::Sell;
                int id = stoi(tokens[2]);
                int price = stoi(tokens[3]);
                int quantity = stoi(tokens[4]);
                int peakSize = quantity; // For limit orders, peak size equals total quantity
                engine.insertOrder(side, id, price, quantity, peakSize);
            } else if (type == 'I' && tokens.size() == 6) {
                // Iceberg Order
                char side_char = tokens[1][0];
                Side side = (side_char == 'B') ? Side::Buy : Side::Sell;
                int id = stoi(tokens[2]);
                int price = stoi(tokens[3]);
                int quantity = stoi(tokens[4]);
                int peakSize = stoi(tokens[5]);
                engine.insertOrder(side, id, price, quantity, peakSize);
            }
        } else if (type == 'C' && tokens.size() == 2) {
            // Cancel Order
            int id = stoi(tokens[1]);
            engine.cancelOrder(id);
        }
        // Ignore other types as per requirements
    }

    return 0;
}
