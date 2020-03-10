//２部グラフ判定
using Graph = vector<vector<int>>;

// 1:黒 0:白 -1:未訪問
vector<int> color;
bool dfs(const Graph &g, int v, int cur = 0) {
    color[v] = cur;
    for (auto next_v : g[v]) {
        if (color[next_v] != -1) {
            (color[next_v] == cur) return false;
            continue;
        }
        if (!dfs(g, next_v, 1 - cur)) return false;
    }
    return true;
}

