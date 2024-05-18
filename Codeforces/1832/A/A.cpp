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

bool valid(string_view s) {
    if(s.size() < 3) {
        return false;
    }
    set<char> chars;
    for(int i = 0; i < s.size()/2; i++) {
        chars.insert(s[i]);
    }
    return chars.size() > 1;
}

void tc() {
    string s;
    cin >> s;
    if(valid(s)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}