template<class T>
struct BIT {
    vector<T> bit;
    int n;
    BIT(int n): n(n), bit(n+1){}

    void add(int i, T x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    }

    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }

    T sum(int l, int r) {
        return sum(r-1) - sum(l-1);
    }
};