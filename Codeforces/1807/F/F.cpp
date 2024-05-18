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

struct coord_t {
    int i, j;
    bool d_i, d_j;
    bool operator <(const coord_t& y) const {
        return std::tie(i, j, d_i, d_j) < std::tie(y.i, y.j, y.d_i, y.d_j);
    }
};

tuple<int, int> move_to_wall(coord_t coords, int n, int m) {
    int i_dist, j_dist;
    if(coords.d_i) {
        i_dist = n-coords.i;
    } else {
        i_dist = coords.i-1;
    }
    if(coords.d_j) {
        j_dist = m-coords.j;
    } else {
        j_dist = coords.j-1;
    }
    int dist = min(i_dist, j_dist);

    if(coords.d_i) {
        coords.i += dist;
    } else {
        coords.i -= dist;
    }
    if(coords.d_j) {
        coords.j += dist;
    } else {
        coords.j -= dist;
    }
    return {coords.i, coords.j};
}

bool is_between(int target_i, int target_j, int start_i, int start_j, int end_i, int end_j) {
    int di1 = target_i - start_i, di2 = end_i - start_i;
    int dj1 = target_j - start_j, dj2 = end_j - start_j;
    return ((start_i <= target_i && target_i <= end_i) || (end_i <= target_i && target_i <= start_i ))
    && ((start_j <= target_j && target_j <= end_j) || (end_j <= target_j && target_j <= start_j))
    &&
            (((di1 == dj1) && (di2 == dj2)) || ((di1 == -dj1) && (di2 == -dj2)));
}

void tc() {
    int n, m, i1, j1, i2, j2;
    string d;
    cin >> n >> m >> i1 >> j1 >> i2 >> j2 >> d;

//    coord_t coord{};
//    int &i = coord.i = i1, &j= coord.j = j1;
//    bool &d_i = coord.d_i, &d_j = coord.d_j; //true = increasing

    int i = i1, j= j1;
    bool d_i, d_j; //true = increasing

    if(d[0] == 'U') {
        d_i = false;
    } else if(d[0] == 'D') {
        d_i = true;
    } else {
        throw "unexpected";
    }
    if(d[1] == 'L') {
        d_j = false;
    } else if(d[1] == 'R') {
        d_j = true;
    } else {
        throw "unexpected";
    }

    //TODO: check for special case where ball reaches without bouncing

    int bounces = 0;
    set<coord_t> seen;

    while(true) {
        if(seen.count({i, j, d_i, d_j})) {
            cout << -1 << "\n";
            return;
        }
        
        //find bounce point
        int new_i, new_j;
        tie(new_i, new_j) = move_to_wall({i, j, d_i, d_j}, n, m);
        
        //check if target on diag
        if(is_between(i2, j2, i, j, new_i, new_j)) {
            cout << bounces << "\n";
            return;
        }

        //mark seen
        seen.insert({i, j, d_i, d_j});

        //update directions
        i = new_i;
        j = new_j;
        if(i == 1 || i == n) {
            d_i = !d_i;
        }
        if(j == 1 || j == m) {
            d_j = !d_j;
        }
        bounces++;
    }
}