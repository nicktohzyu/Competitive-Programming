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

class UFDS{
    struct elem {
        int parent, rank;
    };
    vector<elem> arr;
public:

//returns index of root and flattens
    int find(int i) {
        if (i != arr[i].parent) {
            arr[i].parent = find(arr[i].parent);
        }
        return arr[i].parent;
    }

    void join(int i, int j) {
        i = find(i);
        j = find(j);
        if (arr[i].rank > arr[j].rank) {
            arr[j].parent = i;
        } else if (arr[i].rank < arr[j].rank) {
            arr[i].parent = j;
        } else {
            arr[j].rank++;
            arr[i].parent = j;
        }
    }

    explicit UFDS(int N) {
        arr = *(new vector<elem>());
        arr.reserve(N);
        REP(i, N) {
            arr.push_back({i, 0});
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    UFDS ufds(N);
    while(Q--){
        char c;
        int a, b;
        cin >> c >> a >> b;
        if(c == '='){
            ufds.join(a, b);
        }
        if(c == '?'){
            if(ufds.find(a) == ufds.find(b)){
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }

    return 0;
}