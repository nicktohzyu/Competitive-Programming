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
    int n, m;
    cin >> n;
    VI A(n), B(n);
    REP(i, n) {
        cin >> A[i];
    }
    REP(i, n) {
        cin >> B[i];
    }

    cin >> m;
    VI D(m);
    REP(i, m) {
        cin >> D[i];
    }

    unordered_map<int, int> needed; //val->count
    unordered_set<int> B_values;
    REP(i, n) {
        B_values.insert(B[i]);
        if (A[i] != B[i]) {
            needed[B[i]]++;
        }
    }

    if (!B_values.count(D[m-1])) {
        // an uncovered value
        cout << "NO\n";
        return;
    }

    for (int d : D) {
        needed[d]--;
    }

    int missing = false;
    for (auto [k, v] : needed) {
        if (v > 0) {
            missing = true;
        }
    }

    if (!missing) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}