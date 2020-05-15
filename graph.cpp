//２部グラフ判定
using Graph = vector<vector<int>>;

// 1:黒 0:白 -1:未訪問
vector<int> color;
bool dfs(const Graph &g, int v, int cur = 0) {
    color[v] = cur;
    for (auto next_v : g[v]) {
        if (color[next_v] != -1) {
            (color[next_v] == cur) return false;
            continue;
        }
        if (!dfs(g, next_v, 1 - cur)) return false;
    }
    return true;
}

// warshall_floyd
void warshall_floyd(vvint &d, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (d[j][i] == inf || d[i][k] == inf) continue;
                d[j][k] = min(d[j][k],d[j][i]+d[i][k]);
            }
        }
    }
}

// dijkstra
struct dijkstra {
    struct edge{int to, cost;};
    int V;
    vint d;
    vector<vector<edge>> G;

    dijkstra(int n) {init(n);} 

    void init(int n) {
        V = n;
        G.resize(V);
        d.resize(V);
        rep(i,V) d[i] = inf;
    }

    void add_edge(int s, int t, int cost) {
        s--; t--;
        edge e;
        e.to = t; e.cost = cost;
        G[s].push_back(e);
    }

    void run(int s) {
        s--;
        priority_queue<P, vector<P>, greater<P>> q;
        d[s] = 0;
        q.push(P(0,s));
        while (!q.empty()) {
            P e = q.top(); q.pop();
            int v = e.second;
            if (d[v] < e.first) continue;
            for (auto e: G[v]) {
                if (chmin(d[e.to],d[v]+e.cost)) {
                    q.push(P(d[e.to],e.to));
                }
            }
        }
    }
};

// kruscal(O(ElogV))
template<class T> 
struct edge {int from, to; T cost;};

template<class T>
T kruskal(vector<edge<T>> &edges, int V) {
    sort(edges.begin(),edges.end(),[](const edge<T> &edge1, const edge<T> &edge2) {
        return edge1.cost < edge2.cost;
    });
    union_find uf(V);
    T res = 0;
    for (edge<T> &e: edges) if (uf.unite(e.from,e.to)) res += e.cost;
    return res;
}