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

bool has_special(int l, int r, VI& nums) {
    int k = r-l+1;
    cout << "? " << k << " ";
    for(int i = l; i <= r; i++) {
        cout << " " << i;
    }
    cout << endl;
    int x;
    cin >> x;
    for(int i = l; i <= r; i++) {
        x -= nums[i];
    }
    if(x == 0) {
        return false;
    } else if(x == 1) {
        return true;
    } else {
        throw "unexpected";
    }
//    cout.flush();
}

void tc() {
    int n;
    cin >> n;
    VI nums(n+1); //can prefix sum
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    int l = 1, r = n;
    while(l < r) {
        int m = (l+r)/2;
        if(has_special(l, m, nums)) {
            r = m;
        } else {
            l = m+1;
        }
    }
    cout << "! " << l << endl;
//    cout.flush();
}