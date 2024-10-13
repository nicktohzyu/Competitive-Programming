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

int longestWindow2d (int k, vector<vector<int>>& screen);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> screen;
    REP (i, N) {
        vector<int> row;
        REP (j, M) {
            int pixel;
            cin >> pixel;
            row.push_back(pixel);
        }
        screen.push_back(row);
    }
    cout << longestWindow2d(K, screen);
    return 0;
}

int longestWindow2d (int k, vector<vector<int>>& screen) {
    const int N = screen.size(), M = screen[0].size();
    vector<vector<int>> psum_screen;
    for (vector<int>& row : screen) {
        int current_size = 0;
        vector<int> psum_row;
        for (int pixel : row) {
            if (pixel) {
                current_size++;
            } else {
                current_size = 0;
            }
            psum_row.push_back(current_size);
        }
        psum_screen.push_back(std::move(psum_row));
    }

    int ans = 0;
    for (int j = 0; j < M; j++) {
        int col_size = 0;
        for (int i = 0; i < N; i++) {
            if (psum_screen[i][j] < k) {
                // rectangle is not wide enough
                col_size = 0;
                continue;
            }
            col_size++;
            ans = max(ans, col_size);
        }
    }
    return ans;
}