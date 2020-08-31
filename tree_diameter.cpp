template<class T>
struct tree_diameter {
    struct Edge {int to; T cost;};
    int V;
    vector<vector<Edge>> G;
    tree_diameter(int n) : V(n) {G.resize(n);}
    void add_edge(int a, int b, T cost) {
        G[a].push_back(Edge{b,cost});
        G[b].push_back(Edge{a,cost});
    }
    pair<T,int> dfs(int u, int p = -1) {
        pair<int,int> res = make_pair(0,u);
        for (auto e : G[u]) {
            if (e.to == p) continue;
            auto next = dfs(e.to,u);
            next.first += e.cost;
            res = max(res,next);
        }
        return res;
    }
    //(s,t,l) s-tが長さlの直径
    tuple<int,int,T> run() {
        pair<T,int> p = dfs(0);
        pair<T,int> q = dfs(p.second);
        return make_tuple(p.second,q.second,q.first);
    }
};