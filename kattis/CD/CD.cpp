#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, temp, ans;
    set<int> CDs;
    while(cin >> n >> m && n != 0 || m!= 0){
        CDs.clear();
        ans = 0;
        REP(i, n){
            cin >> temp;
            CDs.insert(temp);
        }
        REP(i, m){
            cin >> temp;
            if(CDs.find(temp) != CDs.end()){
                ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}