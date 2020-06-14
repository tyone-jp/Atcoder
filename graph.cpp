// kruscal(O(ElogV))
template<class T> 
struct edge {int from, to; T cost;};

template<class T>
T kruskal(vector<edge<T>> &edges, int V) {
    sort(edges.begin(),edges.end(),[](const edge<T> &edge1, const edge<T> &edge2) {
        return edge1.cost < edge2.cost;
    });
    union_find uf(V);
    T res = 0;
    for (edge<T> &e: edges) if (uf.unite(e.from,e.to)) res += e.cost;
    return res;
}