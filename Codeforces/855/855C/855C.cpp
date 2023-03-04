#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

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
    vector<int> cards(n);
    int heroes = 0;
    priority_queue<int, vector<int>, greater<>> bonuses;
    REP(i, n) {
        cin >> cards[i];
    }
    std::reverse(cards.begin(), cards.end());
    for(int v : cards) {
        if(v == 0){
            heroes++;
            continue;
        }
        bonuses.push(v);
        if(bonuses.size() > heroes) {
            bonuses.pop();
        }
    }
    long long ans = 0;
    while(!bonuses.empty()){
        ans += bonuses.top();
        bonuses.pop();
    }
    cout << ans << "\n";
}