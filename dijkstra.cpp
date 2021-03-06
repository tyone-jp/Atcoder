// dijkstra(O((E+V)log(V)))
template<class T>
struct dijkstra {
    struct edge{
        int to;
        T cost;
    };
    vector<T> d;
    vector<vector<edge>> G;
    T init_v;
    int N;

    dijkstra(int n, T init_v) : N(n), init_v(init_v) {init(n);} 

    void init(int n) {
        G.resize(n);
        d.resize(n);
    }

    void add_edge(int s, int t, T cost) {
        edge e;
        e.to = t; e.cost = cost;
        G[s].push_back(e);
    }

    void run(int s) {
        rep(i,N) d[i] = init_v;
        priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> q;
        d[s] = 0;
        q.push(pair<T,int>(0,s));
        while (!q.empty()) {
            pair<T,int> e = q.top(); q.pop();
            int v = e.second;
            if (d[v] < e.first) continue;
            for (auto e: G[v]) {
                if (chmin(d[e.to],d[v]+e.cost)) {
                    q.push(pair<T,int>(d[e.to],e.to));
                }
            }
        }
    }
};