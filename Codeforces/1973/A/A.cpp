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
    vector<int> p(3);
    REP(i, 3) {
        cin >> p[i];
    }
    if ((p[0] + p[1] + p[2]) % 2) {
        cout << -1 << "\n";
        return;
    }
    int ans = 0;
    while (p[1] > 0) {
        p[1]--;
        p[2]--;
        std::sort(p.begin(), p.end());
        ans++;
    }
    cout << ans << "\n";
}