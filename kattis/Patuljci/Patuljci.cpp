#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int arr[9];
    REP(i, 9){
        cin >> arr[i];
    }
    int sum = accumulate(arr, arr+9, 0);
    int diff = sum - 100;

    //choose two indexes that sum to diff, guaranteed unique
    int a, b; //index of the two
    REP(i, 9){
        FOR(j, i+1, 9, 1){
            if(arr[i] + arr[j] == diff){
                a = i;
                b = j;
            }
        }
    }
    REP(i, 9){
        if(i == a || i == b){
            continue;
        }
        cout << arr[i] << "\n";
    }
    return 0;
}