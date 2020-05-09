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

// union-find
struct union_find {
    vector<int> data;

    union_find(int size) {data.resize(size,-1);}

    int find(int x) {
        if (data[x] < 0) {return x;}
        return data[x] = find(data[x]);
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) {return false;}
        if (data[x] > data[y]) swap(x,y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int size(int x) {return -data[find(x)];}
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

//dinic法
struct max_flow {
    struct edge {int to, cap, rev;};
    int V;
    vector<vector<edge>> G;
    vector<int> itr, level;

    max_flow(int V) : V(V), G(V){}

    void add_edge(int from, int to, int cap) {
        G[from].push_back((edge){to, cap, (int)G[to].size()});
        G[to].push_back((edge){from, 0, (int)G[from].size()-1});
    }

    void bfs(int s) {
        level.assign(V,-1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e: G[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = itr[v]; i < (int)G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f,e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    int run(int s, int t) {
        int ret = 0, f;
        while (bfs(s), level[t] >= 0) {
            itr.assign(V,0);
            while ((f = dfs(s,t,inf)) > 0) ret += f;
        }
        return ret;
    }
};