template<class Data, class T> 
struct ReRooting {
    struct Node {
        int to, rev;
        Data data;
    };

    using F1 = function<T(T,T)>;
    using F2 = function<T(T,Data)>;

    vector<vector<Node>> G;
    //左からと右からの累積dp
    vector<vector<T>> ldp, rdp;
    //左から親までの累積と右から親の手前までの累積dp
    vector<int> lptr, rptr;
    //累積にf2の値をmergeまたは左からと右からの累積のmerge
    const F1 f1;
    //親にmergeできるように子を引き上げる
    const F2 f2;
    //単位元
    const T ident;

    ReRooting(int n, const F1 &f1, const F2 &f2, const T &ident) : 
        G(n), ldp(n), rdp(n), lptr(n), rptr(n), f1(f1), f2(f2), ident(ident) {}
    
    void add_edge(int u, int v, Data d) {
        G[u].emplace_back(Node{v,(int)G[v].size(),d});
        G[v].emplace_back(Node{u,(int)G[u].size()-1,d});
    }
    //双方向の辺
    void add_edge_bi(int u, int v, Data d, Data e) {
        G[u].emplace_back(Node{v,(int)G[v].size(),d});
        G[v].emplace_back(Node{u,(int)G[u].size()-1,e});
    }
    T dfs(int idx, int par) {
        while (lptr[idx] != par && lptr[idx] < (int)G[idx].size()) {
            auto &e = G[idx][lptr[idx]];
            ldp[idx][lptr[idx]+1] = f1(ldp[idx][lptr[idx]],f2(dfs(e.to,e.rev),e.data));
            lptr[idx]++;
        }
        while (rptr[idx] != par && rptr[idx] >= 0) {
            auto &e = G[idx][rptr[idx]];
            rdp[idx][rptr[idx]] = f1(rdp[idx][rptr[idx]+1],f2(dfs(e.to,e.rev),e.data));
            rptr[idx]--;
        }
        if (par < 0) return rdp[idx][0];
        return f1(ldp[idx][par],rdp[idx][par+1]);
    }
    vector<T> solve() {
        for (int i = 0; i < (int)G.size(); i++) {
            ldp[i].assign(G[i].size()+1,ident);
            rdp[i].assign(G[i].size()+1,ident);
            lptr[i] = 0;
            rptr[i] = (int)G[i].size() - 1; 
        }
        vector<T> res;
        for (int i = 0; i < (int)G.size(); i++) {
            res.push_back(dfs(i,-1));
        }
        return res;
    }
};