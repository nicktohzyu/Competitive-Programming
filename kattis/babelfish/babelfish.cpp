#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    unordered_map<string, string> dict;
    while(getline(cin, s) && !s.empty()){
        istringstream is(s);
        string en, fr;
        is >> en >> fr;
        dict[fr] = en;
    }
    while(getline(cin, s) && !cin.eof()){
        string en = dict[s];
        if(en.empty()){
            en = "eh";
        }
        cout << en << "\n";
    }
    return 0;
}