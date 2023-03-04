#include<iostream>
#include<unordered_map>

using namespace std;

void tc();

int main()
{
    int t;
    cin >> t;
    while (t--) {
        tc();
    }
}

void tc() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    unordered_map<char, int> counts;
    for (char c : s) {
        counts[c]++;
    }
    int ans = 0, operable = 0;
    for (char lc = 'a', uc = 'A'; lc <= 'z'; lc++, uc++) {
        int count1 = counts[lc], count2 = counts[uc];
        int diff = abs(count1 - count2);
        int base = min(count1, count2);
        ans += base;
        operable += diff / 2;
    }
    ans += min(operable, k);
    cout << ans << endl;
}