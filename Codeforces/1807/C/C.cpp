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
    string s;
    cin >> n >> s;
    unordered_map<char, char> mapping;
    REP(i, n) {
        char &c = s[i];
        char digit = i%2 + '0';
        if(mapping.count(c)) {
            if(mapping[c] != digit) {
                cout << "no\n";
                return;
            }
        } else {
            mapping[c] = digit;
        }
        c = mapping[c];
    }
    cout << "yes\n";
}