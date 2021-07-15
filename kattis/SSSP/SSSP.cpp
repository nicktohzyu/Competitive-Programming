#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define INF (int)1e9
#define MP make_pair
#define PB push_back

using namespace std;

typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<PII> VII;

class Graph {
    int V;
    VII *adj;


public:
    Graph(int V) {
        this->V = V;
        adj = new VII[V];
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
    }

    VI dijkstra(int s) {
        VI dist(V, INF);
        dist[s] = 0;
        priority_queue<PII, VII, greater<PII>> pq; //<dist, node>
        pq.push(MP(0, s));
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            VII edges = adj[u];
            REP(i, edges.size()) {
                int v = edges[i].first, w = edges[i].second;
                int newDist = dist[u] + w;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    pq.push(MP(newDist, v));
                }
            }
        }
        return dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, q, s;
    while ((cin >> n >> m >> q >> s) &&
           !(n == 0 && m == 0 && q == 0 && s == 0)) {
        Graph g(n);
        REP(i, m) {
            int u, v, w;
            cin >> u >> v >> w;
            g.addEdge(u, v, w);
        }
        VI dist = g.dijkstra(s);
        REP(i, q) {
            int v;
            cin >> v;
            if (dist[v] < INF) {
                cout << dist[v] << "\n";
            } else {
                cout << "Impossible\n";
            }
        }

    }
    return 0;
}