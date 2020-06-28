struct bipartite {
    vector<int> color;
    vector<vector<int>> g;
    bipartite(int n) {
        color.assign(n,-1);
        g.resize(n);
    }
    void add_edge(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    bool is_bipartite(int v, int cur = 0) {
        color[v] = cur;
        for (int n_v : g[v]) {
            if (color[n_v] != -1) {
                if (color[n_v] == cur) return false;
                continue;
            }
            if (!is_bipartite(n_v,1-cur)) return false;
        }
        return true;
    }
};