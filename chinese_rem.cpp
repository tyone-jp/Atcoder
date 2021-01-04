inline ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x); //xにyの値を入れている
    y -= a / b * x;
    return d;
}

//r0(mod m0)を返す
pair<ll, ll> chinese_rem(const vector<ll> &r, const vector<ll> &m) {
    ll r0 = 0, m0 = 1;
    for (int i = 0; i < (int)r.size(); i++) {
        ll r1 = mod(r[i], m[i]), m1 = m[i];
        if (m0 < m1) {
            swap(m0, m1);
            swap(r0, r1);
        }
        if (m0 % m1 == 0) {
            //r0 ≡ r1 (mod m1)
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        ll p, q;
        ll g = ext_gcd(m0, m1, p, q);
        ll u1 = m1 / g;
        if ((r1 - r0) % g != 0) return {0, 0};
        ll tmp = (r1 - r0) / g % u1 * p % u1;
        r0 += m0 * tmp;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}