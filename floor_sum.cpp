ll floor_sum(ll n, ll m, ll a, ll b) {
    ll res = 0;
    if (a >= m) {
        res += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        res += n * (b / m);
        b %= m;
    }
    ll y_max = (a * n + b) / m;
    ll x_max = y_max * m - b;
    if (y_max == 0) return res;
    res += (n - (x_max + a - 1) / a) * y_max;
    res += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return res;
}