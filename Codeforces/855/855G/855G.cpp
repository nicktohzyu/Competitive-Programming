#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

void tc();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        tc();
    }
    return 0;
}

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef int_fast64_t hash_t;
typedef pair<hash_t, bool> node_stats_t; //hash, is symmetrical
const hash_t P1 = 42, P2 = 179;

node_stats_t dfs(const VVI &nodes, int my_idx, int parent_idx) {
    vector<node_stats_t> children;
    for(int child_idx : nodes[my_idx]) {
        if(child_idx == parent_idx) {
            continue;
        }
        children.push_back(dfs(nodes, child_idx, my_idx));
    }
    std::sort(children.begin(), children.end());

    hash_t my_hash = 0;
    hash_t p_pow = 1;
    // need: counts of each hash, whether odd counts are symm
    unordered_map<hash_t, int> child_counts;
    unordered_map<hash_t, bool> child_symm;
    for(auto [hash, is_symm] : children) {
        child_counts[hash]++;
        child_symm[hash] = is_symm;

        my_hash += P1 + hash*hash + hash*p_pow;
        p_pow *= P2;
    }

    bool is_symm = true;
    bool has_odd_child = false;
    for(auto [child_hash, count] : child_counts) {
        if(count & 1) {
            //more than one odd child, or any odd child is not symm
            if(has_odd_child || !child_symm[child_hash]) {
                is_symm = false;
                break;
            }
            has_odd_child = true;
        }
    }

    return {my_hash, is_symm};
}

void tc() {
    int n;
    cin >> n;
    VVI nodes(n + 1); //1-indexed data
    REP(i, n-1) {
        int a, b;
        cin >> a >> b;
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }
    cout << (dfs(nodes, 1, 0).second ? "YES" : "NO") << "\n";
}
