#include <bits/stdc++.h>
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
using namespace std;
typedef vector<int> VI;
ostream& operator << (ostream& oss, VI& v) {
    REP(i, v.size()) {
        oss << v[i] << " ";
    }
    return oss;
}
void tc();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        tc();
    }
    return 0;
}

void tc() {
    int n, k;
    cin >> n >> k;
    VI nums(n);
    string s;
    cin >> s;
    unordered_map<char, int> counts;
    int ans = 0;
    for (char c : s) {
        counts[c]++;
    }
    for (char c = 'A'; c <= 'G'; c++) {
        ans += max(0, k-counts[c]);
    }
    cout << ans << endl;
}