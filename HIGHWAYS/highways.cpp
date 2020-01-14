#include <iostream>
#include <queue>

using namespace std;

struct edge {
    int v;
    int w;
};

bool operator<(edge a, edge b) {
    return a.w < b.w;
}

#define INF 10000000

int dist[1000001];

void dijkstra(vector<edge> graph[], int n, int s, int d) {
    int i;

    for (i = 0; i <= n; ++i)
        dist[i] = INF;
    priority_queue<edge> q;
    q.push((edge) {s, 0});
    dist[s] = 0;
    while (!q.empty()) {
        edge p = q.top();
        q.pop();

        for (i = 0; i < graph[p.v].size(); ++i) {
            edge k = graph[p.v][i];
            if (dist[p.v] + k.w < dist[k.v]) {
                dist[k.v] = dist[p.v] + k.w;
                q.push(k);
            }
        }
    }
    (dist[d] != INF) ? cout << dist[d] : cout << "NONE";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t, n, m, s, d;
    int u, v, w, i;
    cin >> t;

    while (t--) {
        cin >> n >> m >> s >> d;
        vector<edge> graph[n + 1];

        for (i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            graph[u].push_back((edge) {v, w});
            graph[v].push_back((edge) {u, w});
        }
        dijkstra(graph, n, s, d);
    }
    return 0;
}