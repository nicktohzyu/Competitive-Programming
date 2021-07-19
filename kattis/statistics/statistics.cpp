#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define INF (int)1e9
#define MP make_pair
#define PB push_back

using namespace std;

typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<PII> VII;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int caseNum = 1, n;
    string fmt = "Case %d: %d %d %d\n";
    while(cin >> n){
        int nmin = INF, nmax = -INF;
        while(n--){
            int t;
            cin >> t;
            nmin = min(nmin, t);
            nmax = max(nmax, t);
        }
        char s[100];
        snprintf(s, 100, fmt.c_str(), caseNum++, nmin, nmax, nmax-nmin);
        cout << s;
        cin.ignore();
    }
    return 0;
}