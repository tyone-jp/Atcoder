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


//union_find
struct union_find {
    //親を定義
    vector<int> parent;

    union_find(int n) {
        //全ての親を−１に初期化
        parent = vector<int>(n,-1);
    }

    //親を返す
    int root(int a) {
        if (parent[a] < 0) return a;
        //子ノードを全て根に繋ぐ
        return parent[a] = root(parent[a]);
    }

    int size(int a) {
        //木のサイズ＝ー根の親の値
        return -parent[root(a)];
    }

    bool connect(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return false;
        //大きいaに小さいbを繋ぐように調整
        if (size(a) < size(b)) swap(a,b);
        //サイズを更新
        parent[a] += parent[b];
        //木を繋ぐ
        parent[b] = a;
        return true;
    }
};