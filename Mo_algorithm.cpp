// O(α(N+Q)√N)
struct Mo {
    vector<int> left, right, order;
    vector<bool> v;
    int width;
    int nl, nr, ptr;

    Mo(int n) : width((int)sqrt(n)), nl(0), nr(0), ptr(0), v(n,false) {}

    // [l,r)
    void insert(int l, int r) {
        left.push_back(l);
        right.push_back(r);
    }

    void build() {
        order.resize(left.size());
        iota(begin(order),end(order),0);
        sort(begin(order),end(order),[&](int a, int b) {
            if (left[a]/width != left[b]/width) return left[a] < left[b];
            return bool((right[a] < right[b]) ^ (left[a] / width % 2));
        });
    }

    int process() {
        if (ptr == (int)order.size()) return -1;
        const auto id = order[ptr];
        while (nl > left[id]) distribute(--nl);
        while (nr < right[id]) distribute(nr++);
        while (nl < left[id]) distribute(nl++);
        while (nr > right[id]) distribute(--nr);
        return order[ptr++];
    }

    inline void distribute(int idx) {
        v[idx].flip();
        if (v[idx]) add(idx);
        else del(idx);
    }

    // a[idx]を足したり引いたりする処理を書く
    void add(int idx);
    void del(int idx);
};

void Mo::add(int idx) {

}

void Mo::del(int idx) {

}
