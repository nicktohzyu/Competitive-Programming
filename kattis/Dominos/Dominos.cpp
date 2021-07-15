#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

void TC();

struct Domino;
vector<Domino *> dominos;
vector<Domino *> stk;

struct Domino {
    int n;
    bool visited;
    vector<Domino *> out;

    void visit() {
        if (visited) {
            return;
        }
        visited = true;
        for (Domino *d:out) {
            d->visit();
        }
        stk.push_back(this);
    }
    void visit2() {
        if (visited) {
            return;
        }
        visited = true;
        for (Domino *d:out) {
            d->visit2();
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        TC();
    }
    return 0;
}

void TC() {
    int numDominos, numEdges, ans = 0;
    cin >> numDominos >> numEdges;
    dominos = vector<Domino *>();
    stk = vector<Domino *>();
    for (int i = 0; i < numDominos + 1; i++) {
        Domino* domino = new Domino();
        domino->n = i;
        domino->visited = false;
        domino->out = vector<Domino *>();
        dominos.push_back(domino);
    }
    for (int i = 0; i < numEdges; i++) {
        int s, d;
        cin >> s >> d;
        dominos[s]->out.push_back(dominos[d]);
    }
    for (int i = 1; i < numDominos + 1; i++) {
        dominos[i]->visit();
    }

    //set all to unvisited
    for (int i = 1; i < numDominos + 1; i++) {
        dominos[i]->visited = false;
    }
    //visit in optimal topo order
    for (int i = stk.size()-1; i >= 0; i--) {
        if (stk[i]->visited){
            continue;
        }
        stk[i]->visit2();
        ans++;
    }
    cout << ans << "\n";
}
