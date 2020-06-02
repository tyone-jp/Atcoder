struct segment_tree {
    int n;
    vint dat;
    segment_tree(int n_) {init(n_);}

    void init(int n_) {
        n = 1;
        while (n < n_) n *= 2;
        dat.resize(2*n-1);
        rep(i,2*n-1) dat[i] = 0;
    }

    //kをaに変更
    void update(int k, int a) {
        k += n-1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = max(dat[k*2+1],dat[k*2+2]);
        }
    }

    //[a,b)のquery,kは節点番号
    int query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return 0;
        if (a <= l && r <= b) return dat[k];
        else {
            int vl = query(a,b,k*2+1,l,(l+r)/2);
            int vr = query(a,b,2*k+2,(l+r)/2,r);
            return max(vl,vr);
        }
    }
};