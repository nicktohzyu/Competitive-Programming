#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

void tc();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        tc();
    }
    return 0;
}

typedef vector<int> VI;

VI get_counts(string_view s) {
    VI counts(26);
    for (char c: s) {
        counts[c - 'a']++;
    }
    return counts;
}

bool can_change(string_view s, string_view t, int n, int k) {
    k = min(k, n);
    if (get_counts(s) != get_counts(t)) {
        return false;
    }
    for (int i = n - k; i < k; i++) {
        if (s[i] != t[i]) {
            return false;
        }
    }
    return true;
}

void tc() {
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;
    cout <<
         (can_change(s, t, n, k) ? "YES" : "NO")
         << "\n";
}