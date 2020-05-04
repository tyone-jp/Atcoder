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

// dijkstra
int n;
vint d(105);
vvint cost(105,vint(105,inf));

void dijkstra(int s) {
    priority_queue<P, vector<P>, greater<P>> q;
    rep(i,n) d[i] = inf;
    d[s] = 0;
    q.push(P(0,s));
    while (!q.empty()) {
        P e = q.top(); q.pop();
        int v = e.second;
        if (d[v] < e.first) continue;
        rep(i,n) {
            if (cost[v][i] == inf) continue;
            if (chmin(d[i],d[v]+cost[v][i])) {
                q.push(P(d[i],i));
            }
        }
    }
}

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