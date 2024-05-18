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
    int n, q;
    cin >> n >> q;
    VI parity(n+1);
    parity[0] = 0;
    FOR(i, 1, n+1, 1) {
        int t;
        cin >> t;
        parity[i] = parity[i-1] + (t%2);
    }
    int total_parity = parity[n];
    REP(i, q) {
        int l, r, k;
        cin >> l >> r >> k;
        int change = parity[r] - parity[l-1];
        if((r-l) % 2 == 0 && k %2 != 0) {
            change++;
        }
        cout << ((total_parity + change) %2 == 1 ? "yes" : "no") << "\n";
    }
}