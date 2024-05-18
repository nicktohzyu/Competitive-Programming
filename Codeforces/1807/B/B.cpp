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
    int n;
    cin >> n;
//    VI nums(n);
    int even = 0, odd = 0;
    REP(i, n) {
        int t;
        cin >> t;
        if(t % 2 == 0) {
            even += t;
        } else {
            odd += t;
        }
    }
    cout << ((even > odd) ? "yes" : "no") << "\n";
}