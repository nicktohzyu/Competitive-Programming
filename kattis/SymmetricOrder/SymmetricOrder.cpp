#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, setNo = 1;
    cin >> n;
    while (n != 0) {
        cout << "SET " + to_string(setNo++) << "\n";
        vector<string> vect;
        string str;
        REP(i, n) {
            cin >> str;
            vect.push_back(str);
        }
        FOR(i, 0, n, 2) {
            cout << vect[i] << "\n";
        }
        int m = n % 2 == 0 ? n - 1 : n - 2;
        for (int i = m; i >= 1; i -= 2) {
            cout << vect[i] << "\n";
        }
        cin >> n;
    }
    return 0;
}