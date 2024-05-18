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
    int n;
    cin >> n;
    VI a(n), b(n);
    REP(i, n) {
        cin >> a[i];
    }
    REP(i, n) {
        cin >> b[i];
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    const int M = 1000000007;
    long long ans = 1;
    auto a_iter = a.begin();
    REP(i, n) {
        while(a_iter != a.end() && *a_iter <= b[i]) {
            a_iter++;
        }
        ans *= (a.end() - a_iter - n + 1 + i);
        ans %= M;
    }
    cout << ans << endl;
}