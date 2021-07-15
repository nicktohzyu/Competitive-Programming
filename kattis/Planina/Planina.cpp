#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, sideLength = 2;
    cin >> n;
    while(n--){
        sideLength = sideLength * 2 - 1;
    }

    cout << sideLength * sideLength;
    return 0;
}