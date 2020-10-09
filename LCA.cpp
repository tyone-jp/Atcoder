struct LCA {
    vector<vector<int>> G;
    int root;
    int V;
    int log_v;
    vector<vector<int>> parent;
    vector<int> depth;
    LCA(int v_, int root_) : root(root_), V(v_) {
        int log_v_ = 0, v = 1;
        while (v < v_) {
            v <<= 1;
            log_v_++;
        }
        log_v = log_v_;
        parent.resize(log_v, vector<int>(v_));
        depth.resize(v_);
        G.resize(v_);
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void dfs(int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for (int i = 0; i < (int)G[v].size(); i++) {
            if (G[v][i] != p) dfs(G[v][i], v, d + 1);
        }
    }

    void init() {
        dfs(0, -1, 0);
        for (int k = 0; k + 1 < log_v; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int k = 0; k < log_v; k++) {
            if ((depth[v] - depth[u]) >> k & 1) {
                v = parent[k][v];
            }
        }
        if (u == v) return u;
        for (int k = log_v - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int dis(int u, int v) {
        int p = lca(u, v);
        return (depth[u] - depth[p]) + (depth[v] - depth[p]);
    }
};