//
// Created by nicho on 11/6/2024.
//
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
int longestWindow (vector<int>& screen) {
    int ans = 0;
    int current_size = 0;
    for (int i = 0; i < screen.size(); i++) {
        if (screen[i]) {
            //working pixel
            current_size++;
            ans = std::max(ans, current_size);
        } else {
            //broken pixel
            current_size = 0;
        }
    }
    return ans;
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