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
    int n, T;
    cin >> n >> T;
    vector<vector<int>> customers(T, vector<int>());
    REP(i, n) {
        int ci, ti;
        cin >> ci >> ti;
        customers[ti].push_back(ci);
    }

    int ans = 0;
    priority_queue<int> pq;
    for(int t = T - 1; t >= 0; t--){
        vector<int> v = customers[t];
        REP(i, v.size()){
            pq.push(v[i]);
        }
        if(!pq.empty()){
            ans += pq.top();
            pq.pop();
        }
    }
    cout << ans << endl;
    return 0;
}