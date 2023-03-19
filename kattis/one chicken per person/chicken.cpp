#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, M;
    cin >> N >> M;
    int diff = abs(N-M);
    bool isPlural = diff > 1;
    cout << "Dr. Chaz ";
    if(N<M){
        cout << "will have " << diff << " piece";
        if(isPlural){
            cout << "s";
        }
        cout << " of chicken left over!";
    } else {
        cout << "needs " << diff << " more piece";
        if(isPlural){
            cout << "s";
        }
        cout << " of chicken!";
    }
    return 0;
}