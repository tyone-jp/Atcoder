struct SCC {
    int V;
    vector<vector<int>> G, rG;
    vector<bool> used;
    vector<int> vs;     //帰りがけ順のならび
    vector<int> cmp;    //属する強連結成分のトポロジカル順序

    SCC(int n) : V(n), G(n), rG(n), used(n), cmp(n) {}

    void add_edge(int from, int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    void dfs(int v) {
        used[v] = true;
        for (int i = 0; i < (int)G[v].size(); i++) {
            if (!used[G[v][i]]) dfs(G[v][i]);
        }
        vs.push_back(v);
    }

    void rdfs(int v, int k) {
        used[v] = true;
        cmp[v] = k;
        for (int i = 0; i < (int)rG[v].size(); i++) {
            if (!used[rG[v][i]]) rdfs(rG[v][i], k);
        }
    }

    int run() {
        used.assign(V, false);
        vs.clear();
        for (int v = 0; v < V; v++) {
            if (!used[v]) dfs(v);
        }
        used.assign(V, false);
        int k = 0;
        for (int i = vs.size() - 1; i >= 0; i--) {
            if (!used[vs[i]]) rdfs(vs[i], k++);
        }
        return k;
    }

    vector<vector<int>> output() {
        run();
        vector<vector<int>> res(*max_element(cmp.begin(), cmp.end()) + 1);
        for (int i = 0; i < (int)cmp.size(); i++) {
            res[cmp[i]].push_back(i);
        }
        return res;
    }
};