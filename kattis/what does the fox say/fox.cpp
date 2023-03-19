#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define INF (int)1e9
#define MP make_pair
#define PB push_back

using namespace std;

void tc() {
    unordered_set<string> sounds;
    string recording, s;
    getline(cin, recording);
    while (getline(cin, s) && s != "what does the fox say?") {
        string sound;
        istringstream sStr(s);
        sStr >> sound >> sound >> sound;
        sounds.insert(sound);
    }
    string sound;
    istringstream recStr(recording);
    while (recStr >> sound) {
        if (sounds.count(sound) == 0) {
            cout << sound << " ";
        }
    }
    cout << "\n";
}

int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);

    int T;
    cin >> T;
    cin.ignore();
    while (T--) {
        tc();
    }
    return 0;
}