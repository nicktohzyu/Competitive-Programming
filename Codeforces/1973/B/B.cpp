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
    VI nums(n);
    int totalBits = 0;
    REP(i, n) {
        cin >> nums[i];
        totalBits |= nums[i];
    }
    int k = 1;
    REP(bit, 21) {
        if(!(totalBits & 1 << bit)) {
            continue;
        }
        int lastIdx = -1;
        int localK = 0;
        REP(i, n) {
            if(!(nums[i] & 1 << bit)) {
                continue;
            }
            int gap = i - lastIdx;
            lastIdx = i;
            localK = max(localK, gap);
        }
        localK = max(localK, n - lastIdx);
        k = max(k, localK);
    }
    cout << k << "\n";
}