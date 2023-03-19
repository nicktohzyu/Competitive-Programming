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

int main(){
    char board[8][8];
    for(int i = 0; i < 8; i++){
        cin >> board[i];
    }
    vector<int> row(16, 0), col(16, 0), rD(16, 0), lD(16, 0);
    int numQ = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == '*'){
                numQ++;
                row[i]++;
                col[j]++;
                rD[i+j]++;
                lD[i-j+7]++;
            }
        }
    }
    if(numQ != 8){
        cout << "invalid";
        return 0;
    }
    for(int i = 0; i < 16; i++) {
        if(row[i] > 1 || col[i] > 1 || lD[i] > 1 || rD[i] > 1){
            cout << "invalid";
            return 0;
        }
    }
    cout << "valid";
    return 0;
}