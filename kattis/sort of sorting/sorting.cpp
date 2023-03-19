#include <bits/stdc++.h>

using namespace std;

int main(){
    struct{
        bool operator()(const string& a, string b){
            return strcmp(a.substr(0, 2).c_str(), b.substr(0, 2).c_str()) < 0;
        }
    } customLess;
    int t;
    while(cin >> t){
        if(t == 0){
            break;
        }
        vector<string> names(t);
        for(int i = 0; i<t; i++){
            cin >> names[i];
        }
        stable_sort(names.begin(), names.end(), customLess);
        for(auto& s : names){
            cout << s << "\n";
        }
        cout << "\n";
    }

    return 0;
}