struct topological_sort{
    vector<vector<int>> G;
    vector<int> indegree;
    vector<int> degree;
    int V;

    topological_sort(int V) : V(V) {
        G.resize(V); 
        indegree.resize(V);
        degree.resize(V);
    }
    void add_edge(int a, int b) {
        G[a].push_back(b);
        indegree[b]++;
    }
    vector<int> sort() {
        queue<int> q;
        vector<int> sorted;
        int deg = 1;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                degree[i] = deg;
            }
        }
        while (!q.empty()) {
            queue<int> q_tmp;
            deg++;
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int i = 0; i < G[v].size(); i++) {
                    int u = G[v][i];
                    indegree[u]--;
                    if (indegree[u] == 0) {
                        q_tmp.push(u);
                        degree[u] = deg;
                    }
                }
                sorted.push_back(v);
            }
            swap(q,q_tmp);
        }
        return sorted;
    }
};