#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int nums[3];
    cin >> nums[0] >> nums[1] >> nums[2];
    sort(nums, nums+3);
    REP(i, 3){
        char temp;
        cin >> temp;
        cout << nums[temp-'A'] << " ";
    }
    return 0;
}