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

void tc(int n){
    bool canBeStack = true, canBeQueue = true, canBePQ = true;
    stack<int> st;
    queue<int> q;
    priority_queue<int> pq;
    while(n--){
        int c, x;
        cin >> c >> x;
        if(c == 1){
            st.push(x);
            q.push(x);
            pq.push(x);
            continue;
        }
        if(canBeStack){
            if(!st.empty() && x == st.top()){
                st.pop();
            } else {
                canBeStack = false;
            }
        }
        if(canBeQueue){
            if(!q.empty() && x == q.front()){
                q.pop();
            } else {
                canBeQueue = false;
            }
        }
        if(canBePQ){
            if(!pq.empty() && x == pq.top()){
                pq.pop();
            } else {
                canBePQ = false;
            }
        }
    }
    if(canBeStack+canBeQueue+canBePQ > 1){
        cout << "not sure\n";
        return;
    }
    if(canBeStack){
        cout << "stack\n";
        return;
    }
    if(canBeQueue){
        cout << "queue\n";
        return;
    }
    if(canBePQ){
        cout << "priority queue\n";
        return;
    }
    cout << "impossible\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while(cin >> n){
        tc(n);
    }
    return 0;
}