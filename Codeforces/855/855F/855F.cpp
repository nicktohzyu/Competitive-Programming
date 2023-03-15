#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

typedef int_fast32_t mask_t;

int n;
long long nightmares = 0;

void do_counting(const vector<mask_t>& contents, const vector<mask_t>& parity, const int banned_idx) {
    unordered_map<mask_t, int> valid_counts; //multiset of parity masks without the banned character
    mask_t banned_mask = (1<<banned_idx);
    mask_t unbanned_mask = ((1<<26) - 1) ^ banned_mask;
    REP(i, n) {
        if((contents[i] & banned_mask) != 0) {
            continue;
        }

        mask_t target = unbanned_mask ^ parity[i];
        nightmares += valid_counts[target];

        valid_counts[parity[i]]++;
    }
}

pair<mask_t, mask_t> get_stats(string_view s) {
    mask_t contents = 0, parity = 0;
    for (char c: s) {
        int bit = c - 'a';
        int bit_idx = 1 << bit;
        contents |= bit_idx;
        parity ^= bit_idx;
    }
    return {contents, parity};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
//    vector<string> words(n);
    vector<mask_t> contents(n), parity(n); //26 bits of mask represent a-z
    REP(i, n) {
        string s;
        cin >> s;
        tie(contents[i], parity[i]) = get_stats(s);

    }

    for (int banned_idx = 0; banned_idx < 26; banned_idx++) {
        do_counting(contents, parity, banned_idx);
    }

    cout << nightmares;
    return 0;
}