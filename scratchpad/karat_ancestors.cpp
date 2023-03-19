/*
Suppose we have some input data describing a graph of relationships between parents and children over multiple generations. The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique positive integer identifier.

For example, in this diagram, 6 and 8 have common ancestors of 4 and 14.

               15
              / \
         14  13  21
         |   |
1   2    4   12
 \ /   / | \ /
  3   5  8  9
   \ / \     \
    6   7     11

pairs = [
    (1, 3), (2, 3), (3, 6), (5, 6), (5, 7), (4, 5),
    (15, 21), (4, 8), (4, 9), (9, 11), (14, 4), (13, 12),
    (12, 9), (15, 13)
]

Write a function that takes this data and the identifiers of two individuals as inputs and returns true if and only if they share at least one ancestor.

Sample input and output:

hasCommonAncestor(pairs, 3, 8)   => false
hasCommonAncestor(pairs, 5, 8)   => true
hasCommonAncestor(pairs, 6, 8)   => true
hasCommonAncestor(pairs, 6, 9)   => true
hasCommonAncestor(pairs, 1, 3)   => false
hasCommonAncestor(pairs, 3, 1)   => false
hasCommonAncestor(pairs, 7, 11)  => true
hasCommonAncestor(pairs, 6, 5)   => true
hasCommonAncestor(pairs, 5, 6)   => true
hasCommonAncestor(pairs, 3, 6)   => true
hasCommonAncestor(pairs, 21, 11) => true

n: number of pairs in the input
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

using id_set_t = unordered_set<int>;
using relationship_t = pair<int, int>;
using adjlist_t = unordered_map<int, unordered_set<int>>;

//child -> set of direct parents
adjlist_t get_adjlist(const vector<relationship_t> &edgelist) {
    adjlist_t adjlist;
    for (const auto &[parent, child]: edgelist) {
        adjlist[child].insert(parent);
    }
    return adjlist;
}

void dfs(id_set_t &ancestors, const adjlist_t &adjlist, int id) {
    if (!adjlist.count(id)) {
        return;
    }
    for (int parent: adjlist.at(id)) {
        ancestors.insert(parent);
        // seen.insert(parent);
        dfs(ancestors, adjlist, parent);
    }
}

unordered_set<int> get_all_ancestors(const adjlist_t &adjlist, int id) {
    id_set_t ancestors;
    dfs(ancestors, adjlist, id);
    return ancestors;
}

void print_adjlist(const adjlist_t &adjlist) {
    for (const auto &kv: adjlist) {
        cout << "child: " << kv.first << " parents: ";
        for (int parent: kv.second) {
            cout << parent << " ";
        }
        cout << endl;
    }
}

bool hasCommonAncestor(vector<relationship_t> edgelist, int id_1, int id_2) {
    adjlist_t adjlist{get_adjlist(edgelist)};
//  print_adjlist(adjlist);
    id_set_t ancestors_1{get_all_ancestors(adjlist, id_1)};
    id_set_t ancestors_2{get_all_ancestors(adjlist, id_2)};

//  cout << "\n ancestors_1:\n";
//  for(auto person_id : ancestors_1) {
//    cout << person_id << " ";
//  }
//  cout << "\n\n ancestors_2:\n";
//  for(auto person_id : ancestors_2) {
//    cout << person_id << " ";
//  }
    return any_of(ancestors_1.begin(), ancestors_1.end(), [&](int i){return ancestors_2.count(i) > 0;});
}


// pair<individual_container_t, individual_container_t> findNodesWithZeroAndOneParents(const vector<relationship_t>& relationships) {
//   unordered_map<int, int> counter;
//   for(const auto& [_, child]: relationships){
//     counter[child]++;
//   }
//   individual_container_t zero_parents, one_parent;

//   for(const auto &[parent_id, child_id] : relationships){
//     if(!counter.count(parent_id)) {
//       zero_parents.insert(parent_id);
//     } else if (counter[parent_id] == 1) {
//       one_parent.insert(parent_id);
//     }

//     if(counter[child_id] == 1) {
//       one_parent.insert(child_id);
//     }
//   }

//   return {zero_parents, one_parent};
// }

int main() {
    vector<pair<int, int>> pairs = {
            make_pair(1, 3),
            make_pair(2, 3),
            make_pair(3, 6),
            make_pair(5, 6),
            make_pair(5, 7),
            make_pair(4, 5),
            make_pair(15, 21),
            make_pair(4, 8),
            make_pair(4, 9),
            make_pair(9, 11),
            make_pair(14, 4),
            make_pair(13, 12),
            make_pair(12, 9),
            make_pair(15, 13)
    };
    cout << hasCommonAncestor(pairs, 3, 8) << endl;
    cout << hasCommonAncestor(pairs, 5, 8) << endl;
    cout << hasCommonAncestor(pairs, 6, 8) << endl;
    cout << hasCommonAncestor(pairs, 6, 9) << endl;
    cout << hasCommonAncestor(pairs, 1, 3) << endl;
    cout << hasCommonAncestor(pairs, 3, 1) << endl;
    cout << hasCommonAncestor(pairs, 7, 11) << endl;
    cout << hasCommonAncestor(pairs, 6, 5) << endl;
    cout << hasCommonAncestor(pairs, 5, 6) << endl;
    cout << hasCommonAncestor(pairs, 3, 6) << endl;
    cout << hasCommonAncestor(pairs, 21, 11) << endl;

// hasCommonAncestor(pairs, 3, 8)   => false
// hasCommonAncestor(pairs, 5, 8)   => true
// hasCommonAncestor(pairs, 6, 8)   => true
// hasCommonAncestor(pairs, 6, 9)   => true
// hasCommonAncestor(pairs, 1, 3)   => false
// hasCommonAncestor(pairs, 3, 1)   => false
// hasCommonAncestor(pairs, 7, 11)  => true
// hasCommonAncestor(pairs, 6, 5)   => true
// hasCommonAncestor(pairs, 5, 6)   => true
// hasCommonAncestor(pairs, 3, 6)   => true
// hasCommonAncestor(pairs, 21, 11) => true
    // auto [zero_parents, one_parent] = findNodesWithZeroAndOneParents(pairs);
    // cout << "zero_parents:\n";
    // for(auto person_id : zero_parents) {
    //   cout << person_id << " ";
    // }
    // cout << "\n\n one_parent:\n";
    // for(auto person_id : one_parent) {
    //   cout << person_id << " ";
    // }
}
