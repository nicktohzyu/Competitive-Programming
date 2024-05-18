#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
using namespace std;
typedef vector<int> VI;

ostream &operator<<(ostream &oss, VI &v) {
    REP(i, v.size()) {
        oss << v[i] << " ";
    }
    return oss;
}

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

typedef pair<int, int> II; // value, initial pos
void tc() {
    int n;
    cin >> n;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    vector<int> unsorted_positions(n), sorted_positions(n);
    std::iota(unsorted_positions.begin(), unsorted_positions.end(), 0); //Initializing
    sort(unsorted_positions.begin(), unsorted_positions.end(), [&](int i, int j) { return nums[i] < nums[j]; });
    for(int i = 0; i < n; i++) {
        sorted_positions[unsorted_positions[i]] = i;
    }
//    cout << sorted_positions;
    vector<VI> DP(n); //[length-1][start]
    //all length 0 and 1 have beauty 0
    DP[0] = VI(n, 0);
    for(int length = 2; length <= n; length++) {

    }
//    long long ans = 0;
//    cout << ans << endl;
}