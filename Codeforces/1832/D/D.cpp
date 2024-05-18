#include <bits/stdc++.h>
#define FOR(i, j, k, in) for (long long i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
using namespace std;
typedef vector<long long> VI;
ostream& operator << (ostream& oss, VI& v) {
    REP(i, v.size()) {
        oss << v[i] << " ";
    }
    return oss;
}

long long tc(VI nums);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    long long q;
    cin >> n >> q;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    while(q--) {
        cout << tc(nums) << "\n";
    }
    return 0;
}

long long tc(VI nums) {
    long long n = nums.size();
    long long original_max_n = nums.back();
    long long k;
    cin >> k;
    for(long long i = 0; i < n && i < k; i++) {
        nums[i] += k-i;
    }
    if((k-n) %2 != 0) {
        nums.back() = original_max_n;
    }
    //find min element and count
    long long min_val = *std::min_element(nums.begin(), nums.end());
    if(n >= k) {
        return min_val;
    }
    long long sum_above_min_val = 0;
    for(long long v : nums) {
        sum_above_min_val += v - min_val;
    }
    long long decrs_needed = (k-n+1)/2;
    if(sum_above_min_val > decrs_needed) {
        decrs_needed = 0;
    } else {
        decrs_needed -= sum_above_min_val;
    }
    min_val -= (decrs_needed+n-1)/n;
    return min_val;
}