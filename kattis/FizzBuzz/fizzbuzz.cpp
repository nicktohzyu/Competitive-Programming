#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y, n;
    cin >> x >> y >> n;
    FOR(i, 1, n+1, 1){
        if(i%x == 0){
            cout << "Fizz";
        }
        if(i%y == 0){
            cout << "Buzz";
        }
        if(i%x && i%y){
            cout << i;
        }
        cout << "\n";
    }

    return 0;
}