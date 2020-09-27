template<class X, class M>  
struct lazy_segment_tree {
    using FX = function<X(X,X)>;
    using FA = function<X(X,M)>;
    using FM = function<M(M,M)>;
    int n;     
    vector<X> dat;
    vector<M> lazy;
    FX fx;
    FA fa;
    FM fm;
    //単位元
    X ex;
    M em;

    lazy_segment_tree(int n_, FX fx_, FA fa_, FM fm_, X ex_, M em_) 
        : fx(fx_), fa(fa_), fm(fm_), ex(ex_), em(em_) {
        n = 1;
        while (n < n_) n *= 2;
        dat.assign(2 * n - 1, ex);
        lazy.assign(2 * n - 1, em);
    }

    void set(int k, X x) {dat[k + n - 1] = x;}
    void build() {
        for (int k = n - 2; k >= 0; k--) {
            dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    void eval(int k) {
        if (lazy[k] == em) return ;
        if (k < n - 1) {        // 子に伝播
            lazy[k * 2 + 1] = fm(lazy[k * 2 + 1], lazy[k]);
            lazy[k * 2 + 2] = fm(lazy[k * 2 + 2], lazy[k]);
        }
        dat[k] = fa(dat[k], lazy[k]);   // 自身を更新
        lazy[k] = em;
    }

    //[a,b)
    void update(int a, int b, M x, int k = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        eval(k);
        if (a <= l && r <= b) {
            lazy[k] = fm(lazy[k], x);
            eval(k);
        } else if (a < r && l < b) {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            dat[k] = fx(dat[k * 2 + 1], dat[k * 2 + 2]);
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
            return fx(vl, vr);
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