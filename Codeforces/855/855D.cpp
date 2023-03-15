#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

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
    string s;
    cin >> s;
    int ans = n-1;
    REP(i, n-2) {
        if(s[i] == s[i+2]) {
            ans--;
        }
    }
    cout << ans << "\n";
}