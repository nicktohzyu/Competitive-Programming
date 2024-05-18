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

const int MAX = 5001;

void tc() {
    int n;
    cin >> n;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    std::sort(nums.begin(), nums.end());
    if(nums[0] != 1) {
        cout << "no\n";
        return;
    }
    long long total = 1;
    for(int i = 1; i < n; i++) {
        int ci = nums[i];
        if(total < ci) {
            cout << "no\n";
            return;
        }
        total += ci;
    }
    cout << "yes\n";
}