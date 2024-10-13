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
    int n, f, k;
    cin >> n >> f >> k;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    if (n == k) {
        cout << "YES\n";
        return;
    }
    int favourite_val = nums[f-1];
    std::sort(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.end());
    // nums[k-1] removed, nums[k] present
    if (nums[k] < favourite_val) {
        cout << "YES\n";
    } else if (nums[k-1] == favourite_val && nums[k] == favourite_val) {
        cout << "MAYBE\n";
    } else {
        cout << "NO\n";
    }
}