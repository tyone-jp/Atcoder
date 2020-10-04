template<class T>
struct segment_tree {
    using F = function<T(T,T)>;
    using C = function<bool(T)>;
    int n_;
    int size;     
    vector<T> dat;
    F f;
    T init_v;

    segment_tree(int n_, T init_v, F f) : n_(n_), f(f), init_v(init_v) {
        size = 1;
        while (size < n_) size *= 2;
        dat.assign(2 * size - 1, init_v);
    }

    //kをaに変更
    void update(int k, T a) {
        k += size - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = f(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    //[a,b)のquery,kは節点番号
    T query(int a, int b, int k = 0, int l = 0, int r = -1) {
        if (r < 0) r = size;
        if (r <= a || b <= l) return init_v;
        if (a <= l && r <= b) return dat[k];
        else {
            T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return f(vl, vr);
        }
    }

    //[l,x)がcheckを満たす最も大きいx
    int max_right(int l, C check) {
        if (l == n_) return n_;
        l += size - 1;
        T v = init_v;
        do {
            while (l % 2 != 0) l >>= 1; //伸ばせるだけのばす
            if (!check(f(v, dat[l]))) {
                while (l < size - 1) {  //葉になるまで再帰
                    l = l * 2 + 1;
                    if (check(f(v, dat[l]))) {
                        v = f(v, dat[l]);
                        l++;
                    }
                }
                return l - size + 1;
            }
            v = f(v, dat[l]);
            l++;
        } while (((l + 1) & -(l + 1)) != (l + 1));  //右端を超えて左端になった時終わり
        return n_;
    }

    //[x,r)がcheckを満たす最も小さいx
    int min_left(int r, C check) {
        if (r == 0) return 0;
        r += size - 1;
        T v = init_v;
        do {    
            r--;
            while (r % 2 == 0) r = r / 2 - 1;
            if (!check(f(dat[r], v))) {
                while (r < size - 1) {
                    r = 2 * r + 2;
                    if (check(f(v, dat[r]))) {
                        v = f(v, dat[r]);
                        r--;
                    }
                }
                return r - size + 2;
            }
        } while (((r + 1) & -(r + 1)) != (r + 1));
        return 0;
    }

    T operator[](int a) {return dat[a + size - 1];}

    //[a,b)を出力
    void debug_seg(int a, int b) {
        a += size - 1; b += size - 1;
        for (int i = a; i < b; i++) {
            cout << dat[i] << " ";
        }
        cout << endl;
    }
};