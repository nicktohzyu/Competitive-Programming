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
    int n, k;
    cin >> n >> k;
    VI nums(n);
    vector<long long> psum(n);
    REP(i, n) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    psum[0] = nums[0];
    for(int i = 1; i < n; i++) {
        psum[i] = psum[i - 1] + nums[i];
    }
    long long best = 0;
    for(int i = 0; i <= k; i++) {
        int l = 2*i;
        int r = n - 1 - k + i;
        long long sum = psum[r];
        if(l > 0) {
            sum -= psum[l-1];
        }
        best = max(best, sum);
    }
    cout << best << "\n";
}