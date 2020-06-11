// warshall_floyd
template<class T>
struct warshall_floyd {
    vector<vector<T>> dis;
    int n;
    T init_v;
    warshall_floyd(int n, T init_v) :init_v(init_v), n(n) {init(n);}

    void init(int n) {
        dis.assign(n,vector<T>(n,init_v));
        rep(i,n) dis[i][i] = 0;
    }

    void add_dis(int s, int t, T cost) {
        dis[s][t] = dis[t][s] = cost;
    }

    void run() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (dis[j][i] == init_v || dis[i][k] == init_v) continue;
                    dis[j][k] = min(dis[j][k],dis[j][i]+dis[i][k]);
                }
            }
        }
    }
};