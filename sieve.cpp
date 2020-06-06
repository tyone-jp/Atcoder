//エラストテネスの篩
struct sieve {
    int n;
    vector<int> f, primes;
    sieve(int n = 1) : n(n), f(n+1) {
        f[0] = f[1] = -1;
        for (ll i = 2; i <= n; i++) {
            if (f[i]) continue;
            primes.push_back(i);
            f[i] = i;
            for (ll j = i * i; j <= n; j += i) {
                if(!f[j]) f[j] = i;
            }
        }
    }
    bool is_prime(int x) {return f[x] == x;}
    // 素因数分解したものを返す(12=2x2x3)
    vector<int> factor_list(int x) {
        vector<int> res;
        while (x != 1) {
            res.push_back(f[x]);
            x /= f[x];
        }
        return res;
    }
    // xが小さいときはエラストテネスの篩を用いて素因数分解
    vector<P> factor(int x) {
        vector<int> fl = factor_list(x);
        if (fl.size() == 0) return {};
        vector<P> res(1,P(fl[0],0));
        for (int p : fl) {
            if (res.back().first == p) {
                res.back().second++;
            } else {
                res.emplace_back(p,1);
            }
        }
        return res;
    }
    vector<pair<ll,int>> factor(ll x) {
        vector<pair<ll,int>> res;
        for (int p : primes) {
            int y = 0;
            while (x % p == 0) {
                x /= p;
                y++;
            }
            if (y != 0) res.emplace_back(p,y);
        }
        if (x != 1) res.emplace_back(x,1);
        return res;
    }
};