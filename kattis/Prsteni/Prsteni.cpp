#include <bits/stdc++.h>
#include "Fraction.h"

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)


using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int arr[n];
    int initial, curr;
    cin >> initial;
    FOR(i, 1, n, 1) {
        cin >> curr;
        Fraction tmp(initial, curr);
        cout << tmp.str() << "\n";
    }
    return 0;
}