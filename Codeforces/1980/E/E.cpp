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
bool tc();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        if (tc()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}

bool tc() {
    int n, m;
    cin >> n >> m;
    vector<VI> A(n, VI(m)), B(n, VI(m));
    REP(i, n) {
        REP(j, m) {
            cin >> A[i][j];
        }
    }
    REP(i, n) {
        REP(j, m) {
            cin >> B[i][j];
        }
    }
    set<set<int>> A_cols, A_rows;

    REP(i, n) {
        set<int> row;
        REP(j, m) {
            row.insert(A[i][j]);
        }
        A_rows.insert(row);
    }
    REP(j, m) {
        set<int> col;
        REP(i, n) {
            col.insert(A[i][j]);
        }
        A_cols.insert(col);
    }

    REP(i, n) {
        set<int> row;
        REP(j, m) {
            row.insert(B[i][j]);
        }
        if (!A_rows.count(row)) {
            return false;
        }
    }
    REP(j, m) {
        set<int> col;
        REP(i, n) {
            col.insert(B[i][j]);
        }
        if (!A_cols.count(col)) {
            return false;
        }
    }
    return true;
}