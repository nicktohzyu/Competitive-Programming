#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> busses;
    for(int i = 0; i < N; i++){
        int t;
        cin >> t;
        busses.push_back(t);
    }
    sort(busses.begin(), busses.end());
    int start = 0, end = 0;
    for(int i = 0; i < N; i++){
        start = busses[i];
        end = busses [i];
        while(i < N && busses[i+1] == end + 1){
            i++;
            end++;
        }
        if(end - start > 1){
            cout << start << "-" << end << " ";
        } else if (end - start == 1){
            cout << start << " " << end << " ";
        } else {
            //start == end
            cout << start << " ";
        }
    }
    return 0;
}