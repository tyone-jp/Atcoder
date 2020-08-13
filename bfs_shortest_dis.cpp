struct bfs_shortest_dis{
    vector<vector<int>> G;
    vector<int> dis;
    vector<int> pre;

    bfs_shortest_dis(int v) {G.resize(v); dis.assign(v,inf); pre.assign(v,-1);}
    void add_dis(int a, int b) {G[a].push_back(b);}
    void run(int s) {
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int n_v : G[v]) {
                if (dis[n_v] > dis[v] + 1) {
                    dis[n_v] = dis[v] + 1;
                    q.push(n_v);
                    pre[n_v] = v;
                }
            }
        }
    }
};