template<class X, class M>  
struct lazy_segment_tree {
    using Op = function<X(X,X)>;
    using Mapping = function<X(X,M)>;
    using Composition = function<M(M,M)>;
    int n;     
    vector<X> dat;
    vector<M> lazy;
    Op op;
    Mapping mapping;
    Composition composition;
    //単位元
    X ex;
    M em;

    lazy_segment_tree(int n_, Op op_, Mapping mapping_, Composition composition_, X ex_, M em_) 
        : op(op_), mapping(mapping_), composition(composition_), ex(ex_), em(em_) {
        n = 1;
        while (n < n_) n *= 2;
        dat.assign(2 * n - 1, ex);
        lazy.assign(2 * n - 1, em);
    }

    void set(int k, X x) {dat[k + n - 1] = x;}
    void build() {
        for (int k = n - 2; k >= 0; k--) {
            dat[k] = op(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    void eval(int k) {
        if (lazy[k] == em) return ;
        if (k < n - 1) {        // 子に伝播
            lazy[k * 2 + 1] = composition(lazy[k * 2 + 1], lazy[k]);
            lazy[k * 2 + 2] = composition(lazy[k * 2 + 2], lazy[k]);
        }
        dat[k] = mapping(dat[k], lazy[k]);   // 自身を更新
        lazy[k] = em;
    }

    //[a,b)
    void update(int a, int b, M x, int k = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        eval(k);
        if (a <= l && r <= b) {
            lazy[k] = composition(lazy[k], x);
            eval(k);
        } else if (a < r && l < b) {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            dat[k] = op(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    //[a,b)のquery,kは節点番号
    X query(int a, int b, int k = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(k);
        if (r <= a || b <= l) return ex;
        if (a <= l && r <= b) return dat[k];
        else {
            X vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            X vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }

    X operator[](int a) {return dat[a+n-1];}

    //[a,b)を出力
    void debug_seg(int a, int b) {
        a += n - 1; b += n - 1;
        for (int i = a; i < b; i++) {
            cout << dat[i] << " ";
        }
        cout << endl;
    }
};