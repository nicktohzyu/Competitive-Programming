#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
/*
Input as a binary tree
Hope to output in z-shape

              0
      1              2
   3     4       5       6
  7  8  9  19  11  12  13  14
15 16                27  28

expected output：
0
2
1
3
4
5
6
14
13
12
11
10
9
8
7
15
16
27
28
*/
//not familiar with shared_ptr
struct Node {
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    int value;

    Node() = default;

    Node(int v) : value(v) {}

    virtual ~Node() = default;
};

std::shared_ptr<Node> construct_tree() {
    const size_t total = 17;
    std::vector<std::shared_ptr<Node>> node_vec(total);
    for (size_t i = 0; i < total; i++) {
        node_vec[i] = std::make_shared<Node>(i);
    }
    for (size_t i = 0; i < total; i++) {
        auto &cur = node_vec[i];
        if (i * 2 + 1 < total) {
            cur->left = node_vec[i * 2 + 1];
        }
        if (i * 2 + 2 < total) {
            cur->right = node_vec[i * 2 + 2];
        }
    }

    node_vec[13]->left = std::make_shared<Node>(27);
    node_vec[13]->right = std::make_shared<Node>(28);
    return node_vec[0];
}

// TODO
void print_tree(std::shared_ptr<Node> root) {
    int level = 0;
    vector<shared_ptr<Node>> curr, next;
    curr.push_back(root);
    while (!curr.empty()) {
//        print
        if(level%2 == 0){
            //left to right
            for(int i = 0; i < curr.size(); i++){
                cout << curr[i]->value << "\n";
            }
        } else {
            //right to left
            // curr.size(). size_t
            for(int i = (int)curr.size()-1; i >= 0; i--){
                cout << curr[i]->value << "\n";
            }
        }
//        cout << "\n" << "level: " << level << "\n";
//        for (int i = 0; i < curr.size(); i++) {
//            cout << curr[i]->value << " ";
//        }

        //insert children into next
        for (int i = 0; i < curr.size(); i++) {
            Node n = *(curr[i]);
            if (n.left != nullptr) {
                next.push_back(n.left);
            }
            if (n.right != nullptr) {
                next.push_back(n.right);
            }
        }
        //set curr to next
        curr.clear();
        curr.swap(next);
        level++;
    }
}

int main() {
    auto root = construct_tree();
    print_tree(root);
    return 0;
}