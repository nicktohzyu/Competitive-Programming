#include <ios>
#include <iostream>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, t, cnt = 0;
    cin >> n;
    REP(i, n){
        cin >> t;
        if(t < 0){
            cnt++;
        }
    }
    cout << cnt << "\n";
    return 0;
}