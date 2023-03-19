#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;
int N, M, K;
struct Room {
    int L, R, A;
};
vector<Room> rooms;

int magic(int mask) {
    int pts = 0;
    for (int room = 0; room < N; room++) {
        if (mask & (1 << room)) {
            pts += rooms[room].A;
        }
    }
    return pts;
}

//ways to visit this combination of rooms
//current magic is recovered
//mask = visited rooms, including current position
//pts includes magic gained from the current room
int ways(vector<int> adjList, vector<vector<int>> dp, int mask, int position, int pts) {
    // base case: only starting room
//    if (mask == 0) {
//        return 1;
//    }
    if ((mask ^ (1 << position)) == 0) {
        return 1;
    }

    // check memoized
    if (dp[mask][position] != -1) {
        return dp[mask][position];
    }

    // calculation
    // check if can be reached
    bool reachable = false;
    REP(room, N) {
        if (!((1 << room) & mask)) {
            continue;
        }
        if (adjList[room] & 1 << position) {
            reachable = true;
        }
    }
    if (!reachable) {
        dp[mask][position] = 0;
        return 0;
    }

    int ans = 0; //number of ways to get here from a previous room
    REP(neighbor, N) { //some previous room had access to the current
        if (!(mask & (1 << neighbor)) || neighbor == position) {
            continue;
        }
        //need to "unvisit" this room
        int newMask = mask ^ (1 << position);
        int prevPts = pts - rooms[neighbor].A;
        if (prevPts < rooms[position].L || prevPts > rooms[position].R) {
            //could not have come from this room due to magic point restrictions
            continue;
        }
        ans += ways(adjList, dp, newMask, neighbor, prevPts);
    }

    // memoize
    dp[mask][position] = ans;
    return ans;
}

int tc() {
    cin >> N >> M >> K; //stored as global
    int combis = 1 << N;
    rooms = *(new vector<Room>(N));

    REP(i, N) {
        int L, R, A;
        cin >> L >> R >> A;
        rooms[i] = {L, R, A};
    }

    vector<int> adjList(N);
    REP(i, M) {
        int X, Y;
        cin >> X >> Y;
        //bidirectional edges
        adjList[X] |= 1 << Y;
        adjList[Y] |= 1 << X;
    }

    vector<vector<int>> dp(combis, vector<int>(N, -1));

    int ans = 0;
    REP(mask, combis) {
        //for each room combination
        if (magic(mask) != K) {
            continue;
        }
        //if this combi achieves the desired points K
        //for each end point
        REP(end, N) {
            //find the number of ways to visit it
            ans += ways(adjList, dp, mask, end, K);
        }
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": " << tc() << "\n";
    }
    return 0;
}
