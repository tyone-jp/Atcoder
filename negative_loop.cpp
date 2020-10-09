struct negative_loop {
    struct edge {int from, to, cost;};
    int V;
    int E;
    vector<edge> es;
    vector<int> d;
    negative_loop(int V, int E): V(V), E(E) {
        memset(d,0,sizeof(V))
    }

    void add_edge(int a, int b, int cost) {
        es.push_back(edge{a, b, cost});
    }

    bool find_negative_loop() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < E; j++) {
                edge e = es[j];
                if (chmax(d[e.to], d[e.from] + e.cost) && i == V - 1) {
                    return true;
                }
            }
        }
        return false;
    }
}