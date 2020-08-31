template<class T>
struct BIT {
    vector<T> bit;
    int n;
    BIT(int n): n(n), bit(n+1){}

    // 1-index
    void add(int i, T x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    }
    
    // a_1+a_2+...a_i
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }

    // [l,r)の合計
    T sum(int l, int r) {
        return sum(r-1) - sum(l-1);
    }

    // min{x|a_1+a_2+...+a_x >= w}
    int lower_bound(int w) {
        if (w <= 0) return 0;
        int x = 0, r = 1;
        while (r < n) r <<= 1;
        for (int len = r; len > 0; len = len >> 1) {
            if (x + len < n && bit[x+len] < w) {
                w -= bit[x+len];
                x += len;
            }
        }
        return x + 1;
    }
};