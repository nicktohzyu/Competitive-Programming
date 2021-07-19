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

void reverseColumns(int arr[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0, k = 4 - 1; j < k; j++, k--)
            swap(arr[j][i], arr[k][i]);
}

// Function for do transpose of matrix
void transpose(int arr[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = i; j < 4; j++)
            swap(arr[i][j], arr[j][i]);
}

void rotate(int arr[4][4]) {
    transpose(arr);
    reverseColumns(arr);
}

void print(int arr[4][4]) {
    REP(i, 4) {
        REP(j, 4) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

void squashRow(int arr[4]) {
    queue<int> oldRow, newRow;
    REP(i, 4) {
        if(arr[i] != 0){
            oldRow.push(arr[i]);
        }
        arr[i] = 0;
    }
    if(oldRow.empty()){
        return;
    }
    int tmp = oldRow.front();
    oldRow.pop();
    while(!oldRow.empty()){
        if(tmp == oldRow.front()){
            newRow.push(2*tmp);
            oldRow.pop();
            tmp = 0;
        } else{
            if(tmp != 0){
                newRow.push(tmp);
            }
            tmp = oldRow.front();
            oldRow.pop();
        }
    }
    if(tmp != 0){
        newRow.push(tmp);
    }
    int i = 0;
    while(!newRow.empty()){
        arr[i++] = newRow.front();
        newRow.pop();
    }
}

void squash(int arr[4][4]) {
    REP(i, 4) {
        squashRow(arr[i]);
    }
}

int main() {
//    int test[4] = {8, 4, 16, 2};
//    squashRow(test);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int arr[4][4], move;
    REP(i, 4) {
        REP(j, 4) {
            cin >> arr[i][j];
        }
    }
    cin >> move;
    REP(n, move) {
        rotate(arr);
    }
    squash(arr);
    REP(n, 4 - move) {
        rotate(arr);
    }
    print(arr);
    return 0;
}