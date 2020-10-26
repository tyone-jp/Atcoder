struct V2 {
    double x, y;
    double EPS = 1e-10;
    V2() {}
    V2(double x, double y) : x(x), y(y) {}
    
    double add(double a, double b) {
        if (abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
        return a + b;
    }

    V2 operator + (V2 p) {
        return V2(add(x, p.x), add(y, p.y));
    }
    V2 operator - (V2 p) {
        return V2(add(x, -p.x), add(y, -p.y));
    }
    V2 operator * (double d) {
        return V2(x * d, y * d);
    } 
    double dot(V2 p) {
        return add(x * p.x, y * p.y);
    }
    double det(V2 p) {
        return add(x * p.y, -y * p.x);
    }
};

vector<V2> convex_hull(vector<V2> &ps) {
    int N = ps.size();
    sort(ps.begin(), ps.end(), [](const V2 &p, const V2 &q) {
        if (p.x != q.x) return p.x < q.x;
        return p.y < q.y;
    });
    int k = 0;
    vector<V2> qs(N * 2);
    for (int i = 0; i < N; i++) {
        while (k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    for (int i = N - 2, t = k; i >= 0; i--) {
        while (k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}

bool cmp_x(const V2 &p, const V2 &q) {
    if (p.x != q.x) return p.x < q.x;
    else return p.y < q.y;
};

double dist(V2 p, V2 q) {
    return (p - q).dot(p - q);
};

double convex_diameter(vector<V2> &dat) {
    vector<V2> qs = convex_hull(dat);
    int n = qs.size();
    if (n == 2) return sqrt(dist(qs[0], qs[1]));
    double res = 0;
    int i = 0, j = 0;
    for (int k = 0; k < n; k++) {
        if (!cmp_x(qs[i], qs[k])) i = k;
        if (cmp_x(qs[j], qs[k])) j = k;
    }
    int si = i, sj = j;
    while (i != sj || j != si) {
        res = max(res, dist(qs[i], qs[j]));
        if ((qs[(i + 1) % n] - qs[i]).det(qs[(j + 1) % n] - qs[j]) < 0) {
            i = (i + 1) % n;
        } else {
            j = (j + 1) % n;
        }
    }
    return sqrt(res);
}