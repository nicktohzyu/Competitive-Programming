#include <bits/stdc++.h>
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
using namespace std;
typedef vector<int> VI;
ostream& operator << (ostream& oss, VI& v) {
    REP(i, v.size()) {
        oss << v[i] << " ";
    }
    return oss;
}
void tc();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        tc();
    }
    return 0;
}

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
//        arr = *(new vector<elem>());
        arr.reserve(N);
        REP(i, N) {
            arr.push_back({i, 0});
        }
    }
};

void tc() {
    int n;
    cin >> n;
    VI nums(n);
    REP(i, n) {
        cin >> nums[i];
    }
    VI neighbors(n);
    UFDS ufds(n);
    REP(i, n) {
        //i dance with a
        //a remembers b
        int a = nums[i]-1;
        int b = nums[a]-1;
        if(i != b) {
            neighbors[a]++;
        }
        ufds.join(i, a);
    }
    set<int> groups;
    REP(i, n) {
        groups.insert(ufds.find(i));
    }
    int num_groups = groups.size();
    int unmatched_ends = std::count(neighbors.begin(), neighbors.end(), 0);
    int open_groups = unmatched_ends / 2;
    int closed_groups = num_groups - open_groups;
    int min_groups = closed_groups + min(open_groups, 1);
    cout << min_groups << " " << num_groups << endl;
}