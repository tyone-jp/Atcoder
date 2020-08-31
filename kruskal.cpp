// union-find
struct union_find {
    vector<int> data;

    union_find(int size) {data.resize(size,-1);}

    int find(int x) {
        if (data[x] < 0) {return x;}
        return data[x] = find(data[x]);
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) {return false;}
        if (data[x] > data[y]) swap(x,y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int size(int x) {return -data[find(x)];}
};

//kruskal(O(ElogE))
template<class T> 
struct kruskal {
    struct edge {
        int from, to;
        T cost;
    };
    vector<edge> edges;
    int V;
    kruskal(int v): V(v) {}
    void add_edge(int a, int b, T cost) {
        edges.push_back(edge{a,b,cost});
    }
    T run() {
        sort(edges.begin(),edges.end(),[](const edge &a, const edge &b) {
            return a.cost < b.cost;
        });
        union_find uf(V);
        T res = 0;
        for (edge &e : edges) {
            if (uf.unite(e.to,e.from)) {
                res += e.cost;
            }
        }
        return res;
    }
};