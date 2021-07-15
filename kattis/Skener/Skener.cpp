#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int r, c, zr, zc;
    cin >> r >> c >> zr >> zc;
//    cin.ignore(1000,'\n');
    char arr[r][c];
    REP(i, r) {
        cin >> arr[i];
//        cin.ignore(1000,'\n');
    }
    REP(i, r) {
        REP(_, zr) {
            REP(j, c) {
                REP(_, zc) {
                    cout << arr[i][j];
                }
            }
            cout << "\n";
        }
    }
    return 0;
}