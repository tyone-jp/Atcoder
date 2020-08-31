template<class T>
struct segment_tree {
    using F = function<T(T,T)>;
    int n;     
    vector<T> data;
    F f;
    T init_v;

    segment_tree(int n_, T init_v, F f) : f(f), init_v(init_v) {
        n = 1;
        while (n < n_) n *= 2;
        data.assign(2*n-1,init_v);
    }

    //kをaに変更
    void update(int k, T a) {
        k += n-1;
        data[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            data[k] = f(data[k*2+1],data[k*2+2]);
        }
    }

    //[a,b)のquery,kは節点番号
    T query(int a, int b, int k = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (r <= a || b <= l) return init_v;
        if (a <= l && r <= b) return data[k];
        else {
            T vl = query(a,b,k*2+1,l,(l+r)/2);
            T vr = query(a,b,2*k+2,(l+r)/2,r);
            return f(vl,vr);
        }
    }

    //[a,b)でcheck(v,x)を満たす最右のid
    int find_rightest(int a, int b, T x, F check, int k = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (!check(data[k],x) || r <= a || b <= l) return -1;
        else if (k >= n - 1) return (k-(n-1));
        else {
            int vr = find_rightest(a,b,x,check,2*k+2,(l+r)/2,r);
            if (vr != -1) return vr;
            else return find_rightest(a,b,x,check,2*k+1,l,(l+r)/2);
        }
    }

    //[a,b)でcheck(v,x)を満たす最左のid
    int find_leftest(int a, int b, T x, F check, int k = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (!check(data[k],x) || r <= a || b <= l) return b;
        else if (k >= n - 1) return (k-(n-1));
        else {
            int vl = find_leftest(a,b,x,check,2*k+1,l,(l+r)/2);
            if (vl != b) return vl;
            else return find_leftest(a,b,x,check,2*k+2,(l+r)/2,r);
        }
    }

    T operator[](int a) {return data[a+n-1];}

    //[a,b)を出力
    void debug_seg(int a, int b) {
        a += n-1; b += n-1;
        for (int i = a; i < b; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};