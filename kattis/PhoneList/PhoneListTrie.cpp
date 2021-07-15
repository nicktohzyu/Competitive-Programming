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

class TrieNode{
public:
//    TrieNode *children[10];
    vector<TrieNode*> children = vector<TrieNode*>(10, nullptr);
    bool hasChildren = false;
    bool isEnd = false;
};

bool insert(TrieNode *root, string phoneNumber){
    TrieNode *node = root;
    REP(i, phoneNumber.size()){
        int digit = phoneNumber.at(i) - '0';
        if(node->children[digit] == nullptr){
            node->children[digit] = new TrieNode;
        }
        node = node->children[digit];
        if(node->isEnd){
            return false;
        }
        if(i == phoneNumber.size()-1 && node->hasChildren){
            return false;
        }
        node->hasChildren = true;
    }
    node->isEnd = true;
    return true;
}

bool validate(TrieNode *root, vector<string> phoneNumbers){
    REP(i, phoneNumbers.size()){
        bool success = insert(root, phoneNumbers[i]);
        if(!success){
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<string> phoneNumbers;
        phoneNumbers.reserve(n);
        REP(i, n){
            string s;
            cin >> s;
            phoneNumbers.push_back(s);
        }
        TrieNode *root = new TrieNode;
        if(validate(root, phoneNumbers)){
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}