#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
using namespace std;
typedef vector<int> VI;

ostream &operator<<(ostream &oss, VI &v) {
    REP(i, v.size()) {
        oss << v[i] << " ";
    }
    return oss;
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<int, int, custom_hash> mp;

bool tc();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        if (tc()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}

bool try_remove(VI nums, int idx) {
    nums.erase(nums.begin() + idx);
    VI GCDs;
    FOR (i, 1, nums.size(), 1) {
        GCDs.push_back(gcd(nums[i - 1], nums[i]));
    }
    FOR (i, 1, GCDs.size(), 1) {
        if (GCDs[i - 1] > GCDs[i]) {
            return false;
        }
    }
    return true;
}

bool tc() {
    int n;
    cin >> n;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    VI GCDs;
    FOR (i, 1, n, 1) {
        GCDs.push_back(gcd(nums[i - 1], nums[i]));
    }
    VI idxs;
    FOR (i, 1, GCDs.size(), 1) {
        if (GCDs[i - 1] > GCDs[i]) {
            idxs.push_back(i - 1);
        }
    }
    if (idxs.empty()) {
        return true;
    }
    if (idxs.size() > 2) {
        return false;
    }
    if (idxs.size() == 2 && idxs[0] + 1 != idxs[1]) {
            return false;
    }
    return try_remove(nums, idxs[0])
           || try_remove(nums, idxs[0] + 1)
           || try_remove(nums, idxs[0] + 2);
}