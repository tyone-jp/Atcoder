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

    int size(int x) {return -data[x];}
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
