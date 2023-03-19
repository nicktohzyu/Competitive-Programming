#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        //DP on how many valid decodings for the substring 0..i
        int len = s.length();
        vector<unsigned int> dp(len, 0);
        //1 way to encode length 0
        dp[0] = validSingle(s[0]) ? 1 : 0; //is the first digit a valid encoding
        dp[1] = validDouble(s[0], s[1]);
        if(validSingle(s[1])){
            dp[1] += dp[0];
        }
        for(int i = 2; i < len; i++){
            //one number
            if(validSingle(s[i])){
                dp[i] += dp[i-1];
            }
            //two numbers
            if(validDouble(s[i-1], s[i])){
                dp[i] += dp[i-2];
            }
        }
        return dp[len-1];
    }
    bool validSingle(char a){
        return '1' <= a && a <= '9';
    }
    bool validDouble(char a, char b){
        if(a <= '1'){
            return true;
        }
        if(a == '2' && b <= '6'){
            return true;
        }
        return false;
    }
};
int main(){
    string s;
    cin >> s;
    Solution *soln = new Solution();
    cout << soln->numDecodings(s);
    return 0;
}
