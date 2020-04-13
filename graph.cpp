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


//union_find
struct union_find {
    //親を定義
    vector<int> parent;

    union_find(int n) {
        //全ての親を−１に初期化
        parent = vector<int>(n,-1);
    }

    //親を返す
    int root(int a) {
        if (parent[a] < 0) return a;
        //子ノードを全て根に繋ぐ
        return parent[a] = root(parent[a]);
    }

    int size(int a) {
        //木のサイズ＝ー根の親の値
        return -parent[root(a)];
    }

    bool connect(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return false;
        //大きいaに小さいbを繋ぐように調整
        if (size(a) < size(b)) swap(a,b);
        //サイズを更新
        parent[a] += parent[b];
        //木を繋ぐ
        parent[b] = a;
        return true;
    }
};

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
vint par;
vint depth;

void init (int n) {
    rep(i,n) {
        par[i] = i;
        depth[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) return x;
    else return par[x] = find(par[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (depth[x] < depth[y]) par[x] = y;
    else {
        par[y] = x;
        if (depth[x] == depth[y]) depth[x]++;
    }
}

bool same(int x, int y) {return find(x) == find(y);}

// kruscal
struct edge {int u, v, cost;};

bool comp(const edge &e1, const edge &e2) {
    return e1.cost < e2.cost;
}

edge es[max_E];
int V, E;

int kruskal() {
    sort(es,es+E,comp);
    init(V);
    int res = 0;
    rep(i,E) {
        edge e = es[i];
        if (!same(e.u,e.v)) {
            unite(e.u,e.v);
            res += e.cost;
        }
    }
    return res;
}