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
        cout << (tc() ? "YES" : "NO") << endl;
    }
    return 0;
}

bool odd(int n) {
    return n % 2 == 1;
}
bool tc() {
    int n;
    cin >> n;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    std::sort(nums.begin(), nums.end());
    if(odd(nums[0])) {
        return true;
    }
    for(int v : nums) {
        if(odd(v)) {
            return false;
        }
    }
    return true;
}