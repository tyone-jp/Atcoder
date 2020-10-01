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

struct two_sat {
    int n;
    vector<bool> ans;
    SCC scc;

    two_sat(int n_) : n(n_), ans(n_), scc(2 * n_) {}

    //index_iがfでindex_jがg
    void add_clause(int i, bool f, int j, bool g) {
        scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
        scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
    }

    bool satisfiable() {
        scc.run();
        auto id = scc.cmp;
        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }

    vector<bool> answer() {return ans;}
};