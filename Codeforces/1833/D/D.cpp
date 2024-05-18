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
    REP(i, n) {
        cin >> nums[i];
    }
    //note: here we define the iterator to point past r, as convention of an end iter
    auto largest_elem = max_element(nums.begin(), nums.end());
    VI::iterator l_iter, r_iter;
    if(largest_elem == nums.begin()) {
        auto second_largest_elem = max_element(next(nums.begin()), nums.end());
        if(second_largest_elem == prev(nums.end())) {
            l_iter = r_iter = second_largest_elem;
        } else {
            l_iter = prev(second_largest_elem);
            r_iter = second_largest_elem;
        }
    } else {
        if(largest_elem == prev(nums.end())) {
            l_iter = largest_elem;
            r_iter = nums.end();
        } else {
            l_iter = prev(largest_elem);
            r_iter = largest_elem;
        }
        while(l_iter != nums.begin() && *(prev(l_iter)) > nums[0]) {
            --l_iter;
        }
    }

    VI prefix = VI(nums.begin(), l_iter);
    VI mid = VI(l_iter, r_iter);
    std::reverse(mid.begin(), mid.end());
    VI suffix = VI(r_iter, nums.end());
    cout << suffix << mid << prefix << endl;

//    cout << "suffix: " << suffix << endl;
//    cout << "mid: " << mid << endl;
//    cout << "prefix: " << prefix << endl << endl;
}
