ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x); //xにyの値を入れている
    y -= a / b * x;
    return d;
}

inline ll mod_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

inline ll mod_inv(ll a, ll mod) {
    ll x, y;
    ext_gcd(a, mod, x, y);
    return (mod + x % mod) % mod;
}

template<class T>
inline void bit_reverse(vector<T> &a) {
    int n = a.size();
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
    }
}

template<ll mod, int primitive_root>
struct NTT {
    ll get_mod() const {return mod;}
    void _ntt(vector<ll> &a, bool inverse) {
        const int n = a.size();
        assert((n ^ (n & -n)) == 0);
        const int g = primitive_root;
        ll tmp = (mod - 1) * mod_inv(n, mod) % mod;
        ll h = mod_pow(g, tmp, mod);    //h^n = 1
        if (inverse) h = mod_inv(h, mod);

        bit_reverse(a);

        for (int m = 1; m < n; m <<= 1) {
            const int m2 = 2 * m;
            ll _base = mod_pow(h, n / m2, mod);
            ll _w = 1;
            for (int j = 0; j < m; j++) { 
                for (int k = j; k < n; k += m2) { 
                    ll u =  a[k];
                    ll d = (a[k + m] * _w) % mod;
                    a[k] = (u + d) % mod;
                    a[k + m] = (u - d + mod) % mod;
                }
                _w = (_w * _base) % mod;
            }
        }
    }
    void ntt(vll &input) {_ntt(input, false);}
    void intt(vll &input) {
        _ntt(input, true);
        const ll n_inv = mod_inv((int)input.size(), mod);
        for (auto &x : input) x = (x * n_inv) % mod;
    }

    vll convolution(const vll &a, const vll &b) {
        int result_size = a.size() + b.size() - 1;
        int n = 1;
        while (n < result_size) n <<= 1;

        vll _a = a, _b = b;
        _a.resize(n, 0);
        _b.resize(n, 0);

        ntt(_a);
        ntt(_b);
        for (int i = 0; i < n; i++) {
            _a[i] = (_a[i] * _b[i]) % mod;
        }
        intt(_a);
        _a.resize(result_size);
        return _a;
    }
};

//任意のmodで畳み込み
vll convolution_ntt(vll &a, vll &b, ll mod = 1224736769LL) {
    for (auto &x : a) x %= mod;
    for (auto &x : b) x %= mod;

    NTT<167772161, 3> ntt1;
    NTT<469762049, 3> ntt2;
    NTT<1224736769, 3> ntt3;

    vll x1 = ntt1.convolution(a, b);
    vll x2 = ntt2.convolution(a, b);
    vll x3 = ntt3.convolution(a, b);

    const ll m1 = ntt1.get_mod(), m2 = ntt2.get_mod(), m3 = ntt3.get_mod();
    const ll m1_inv_m2 = mod_inv(m1, m2);
    const ll m12_inv_m3 = mod_inv(m1 * m2, m3);
    const ll m12_mod = m1 * m2 % mod;
    vll res(x1.size());
    //復元
    for (int i = 0; i < (int)x1.size(); i++) {
        ll v1 = (x2[i] - x1[i]) * m1_inv_m2 % m2;
        if (v1 < 0) v1 += m2;
        ll v2 = (x3[i] - (x1[i] + m1 * v1) % m3) * m12_inv_m3 % m3;
        if (v2 < 0) v2 += m3;
        ll v3 = (x1[i] + m1 * v1 + m12_mod * v2) % mod;
        if (v3 < 0) v3 += mod;
        res[i] = v3;
    }
    return res;
}