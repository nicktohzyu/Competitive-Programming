#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;
vector<vector<char>> grid;
vector<vector<int>> regions;
int r, c;

void floodFill(int x, int y, int region, char type);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> r >> c;
    grid = vector<vector<char>>(r);
    regions = vector<vector<int>>(r);
    REP(i, r) {
        grid[i] = vector<char>(c);
        regions[i] = vector<int>(c);
        REP(j, c) {
            cin >> grid[i][j];
        }
    }
    int num = 1;
    //flood floodFill
    REP(i, r) {
        REP(j, c) {
            if (regions[i][j] == 0) {
                floodFill(i, j, num++, grid[i][j]);
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--;
        r2--;
        c1--;
        c2--;
        if (regions[r1][c1] != regions[r2][c2]) {
            cout << "neither\n";
        } else if (grid[r1][c1] == '0') {
            cout << "binary\n";
        } else {
            cout << "decimal\n";
        }
    }
    return 0;
}

void floodFill(int x, int y, int region, char type) {
    if (grid[x][y] != type || regions[x][y] != 0) {
        return;
    }
    regions[x][y] = region;
    if (x > 0) {
        floodFill(x - 1, y, region, type);
    }
    if (y > 0) {
        floodFill(x, y - 1, region, type);
    }
    if (x < r - 1) {
        floodFill(x + 1, y, region, type);
    }
    if (y < c - 1) {
        floodFill(x, y + 1, region, type);
    }
}