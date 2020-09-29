//最小費用流
template<class flow_t, class cost_t>
struct primal_dual {
    using Pui = pair<cost_t, int>;
    struct edge {
        int to, rev;
        flow_t cap;
        cost_t cost;
        edge(int to, flow_t cap, cost_t cost, int rev) 
            : to(to), cap(cap), cost(cost), rev(rev) {}
    };
    int V;
    bool has_negative_edge = false;
    cost_t CINF;
    flow_t FINF;
    vector<vector<edge>> G;
    vector<int> prevv, preve;
    vector<cost_t> h, dis;

    primal_dual(int n, flow_t FINF_, cost_t CINF_) 
        : V(n), FINF(FINF_), CINF(CINF_), G(n), prevv(n, -1), preve(n, -1), h(n, 0), dis(n) {}

    void add_edge(int from, int to, flow_t cap, cost_t cost) {
        has_negative_edge |= cost < 0;
        G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
        G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
    }

    void bellman_ford(int s) {
        rep(i,V) dis[i] = CINF;
        dis[s] = 0;
        bool is_updated = true;
        rep(step,V) {
            is_updated = false;
            rep(i,V) {
                if (dis[i] == CINF) continue;
                rep(j,G[i].size()) {
                    edge e = G[i][j];
                    if (e.cap > 0 && dis[e.to] > dis[i] + e.cost) {
                        dis[e.to] = dis[i] + e.cost;
                        prevv[e.to] = i;
                        preve[e.to] = j;
                        is_updated = true;
                    }
                }
            }
            if (!is_updated) break;
        }
        rep(i,V) {
            if (dis[i] != CINF) h[i] += dis[i];
        }
    }

    void dijkstra(int s) {
        priority_queue<Pui, vector<Pui>, greater<Pui>> que;
        rep(i,V) dis[i] = CINF;
        dis[s] = 0;
        que.push(Pui(0, s));
        while (!que.empty()) {
            Pui p = que.top(); que.pop();
            int v = p.second;
            if (dis[v] < p.first) continue;
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && dis[e.to] > dis[v] + e.cost + h[v] - h[e.to]) {
                    dis[e.to] = dis[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(Pui(dis[e.to], e.to));
                }
            }
        }
        for (int v = 0; v < V; v++) {
            if (dis[v] != CINF) h[v] += dis[v];
        }
    }

    cost_t cal(int s, int t, flow_t f) {
        flow_t d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
        return h[t] * d;
    }

    cost_t run(int s, int t, flow_t f) {
        cost_t res = 0;
        if (has_negative_edge) {
            bellman_ford(s);
            if (dis[t] == CINF) return CINF;
            res += cal(s, t, f);
        }
        while (f > 0) {
            dijkstra(s);
            if (dis[t] == CINF) return CINF;            
            res += cal(s, t, f);
        }
    }

    //流す量が任意の場合
    cost_t run(int s, int t) {
        cost_t res = 0;
        bellman_ford(s);
        if (h[t] >= 0 || dis[t] == CINF) return res;
        flow_t tmp = FINF;
        res += cal(s, t, tmp);
        while (true) {
            dijkstra(s);
            if (h[t] >= 0 || dis[t] == CINF) return res;
            res += cal(s, t, tmp);
        }
    }
};