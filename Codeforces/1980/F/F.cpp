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

class Fountain_t {
public:
    int x{}, y{}, idx{}; //original idx
    bool covered = false;
    int smallest_y_ahead;
    bool operator<(const Fountain_t &other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y > other.y;
        return idx < other.idx;
    }

};

void tc() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<Fountain_t> fountains(k);
    REP(i, k) {
        int x, y;
        cin >> x >> y;
        fountains[i] = {x, y, i};
    }
    std::sort(fountains.begin(), fountains.end());
    long long free_area = 0;
    int prev_x = n;
    int smallest_y = m+1;
    for (int i = k-1; i >= 0; i--) {
        Fountain_t& fountain = fountains[i];
        if(fountain.x < prev_x) {
            free_area += static_cast<long>(smallest_y-1) * static_cast<long>(prev_x - fountain.x);
            prev_x = fountain.x;
        }
        if(smallest_y <= fountain.y) {
            fountain.covered = true;
            continue;
        }
        smallest_y = fountain.y;
    }

    free_area += static_cast<long>(smallest_y-1) * prev_x;
    cout << free_area << "\n";

    vector<long> answers(k);
    for (Fountain_t& fountain : fountains) {
        answers[fountain.idx] = !fountain.covered;
    }
    REP(i, k) {
        cout << answers[i] << " ";
    }
    cout << "\n";
}