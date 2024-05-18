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

int cv(const VI& nums) {
//    if(nums.size() < 2) {
//        return 1;
//    }
//    bool is_increasing = nums[1] > nums[0];
//    int ans = (nums[1] > nums[0]) ? 1 : 2;
//    for(int i = 2; i < nums.size(); i++) {
//        if((nums[i] == nums[i-1])) {
//            continue;
//        }
//        if((nums[i] > nums[i-1]) == is_increasing) {
//            continue;
//        }
//        ans++;
//        is_increasing = !is_increasing;
//    }
    VI b;
    b.push_back(nums[0]); //invars: no pairwise equal; always changes direction
    for(int i = 1; i < nums.size(); i++) {
        const int v = nums[i];
        if(v == b.back()) {
            continue;
        }
        if(b.size() < 2) {
            b.push_back(v);
            continue;
        }
        if((b[b.size() - 2] > b.back()) == (b.back() > v)) {
            b.pop_back();
            b.push_back(v);
        } else {
            b.push_back(v);
        }
    }
    return b.size();
}

void tc() {
    int n;
    cin >> n;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    cout << cv(nums) << "\n";
}