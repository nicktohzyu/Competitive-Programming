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

typedef pair<int, int> II;

void tc() {
    int n, k;
    cin >> n >> k;
    vector<II> A(n);
    VI B(n), ans(n);
    REP(i, n) {
        cin >> A[i].first;
        A[i].second = i;
    }
    REP(i, n) {
        cin >> B[i];
    }
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    REP(i, n) {
        const int day = A[i].second;
        ans[day] = B[i];
    }
    cout << ans << endl;
}