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

    T operator[](int a) {return data[a+n-1];}

    //[a,b)を出力
    void debug(int a, int b) {
        a += n-1; b += n-1;
        for (int i = a; i < b; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};