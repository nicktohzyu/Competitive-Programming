#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define INF (int)1e9
#define MP make_pair
#define PB push_back

using namespace std;

typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<PII> VII;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        bool fail = false;
        int n;
        cin >> n;
        vector<string> phoneNumbers;
        phoneNumbers.reserve(n);
        REP(i, n){
            string s;
            cin >> s;
            phoneNumbers.push_back(s);
        }
        sort(phoneNumbers.begin(), phoneNumbers.end());
        REP(i, n-1){
            size_t l = min(phoneNumbers[i].size(), phoneNumbers[i+1].size());
            if(strncmp(phoneNumbers[i].c_str(), phoneNumbers[i+1].c_str(), l) == 0){
                fail = true;
                break;
            }
        }
        if(fail){
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}