//O(VE)
template<class T>
struct bellman_ford {
    struct edge {
        int to;
        T cost;
    };
    vector<vector<edge>> G;
    vector<vector<edge>> G_rev;
    vector<T> dis;
    vector<T> dis_middle;
    int V;
    T init_v;
    bool negative_loop;

    bellman_ford(int n, T init) : G(n), G_rev(n), dis(n,init), 
        V(n), init_v(init) {}
    void add_edge(int a, int b, T cost) {
        G[a].push_back(edge{b,cost});
        G_rev[b].push_back(edge{a,cost});
    }
    void run(int s) {
        bool update = false;
        dis[s] = 0;
        for (int i = 0; i < V; i++) {
            if (i == V - 1) dis_middle = dis;
            for (int from = 0; from < V; from++) {
                if (dis[from] == init_v) continue;
                for (auto e : G[from]) {
                    if (dis[e.to] > dis[from] + e.cost) {
                        dis[e.to] = dis[from] + e.cost;
                        if (i == V - 1) update = true;
                    }
                }
            }
        }
        negative_loop = update;
    }
    T path(int s, int t) {
        if (!negative_loop) return dis[t];
        else {
            auto can_reach_from_start = can_reach(G,s);
            auto can_reach_from_goal = can_reach(G_rev,t);
            for (int i = 0; i < V; i++) {
                if (can_reach_from_start[i] && can_reach_from_goal[i]) {
                    if (dis_middle[i] != dis[i]) {
                        return -init_v;
                    }
                }
            }
            return dis[t];
        }
    }
    vector<bool> can_reach(const vector<vector<edge>> &G, int s) {
        vector<bool> res(V,false);
        queue<int> q;
        q.push(s);
        res[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto n_v : G[v]) {
                if (res[n_v.to] == false) {
                    q.push(n_v.to);
                    res[n_v.to] = true;
                }
            }
        }
        return res;
    }
};