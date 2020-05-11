//素数の判定
bool is_prime(ll a) {
    bool ok = true;
    if (a == 1) return false;
    if (a == 2) return true;
    else {
        for (int i = 2; i * i <= a; i++) {
            if (a % i == 0) ok = false;
        }
        return ok;
    }
}

//最大公約数と最小公倍数
ll gcd(ll a, ll b) {return(b?gcd(b,a%b):a);}
ll lcm(ll a, ll b) {return(a/gcd(a,b)*b);}

//拡張ユークリッド(返り値はgcd(a,b))
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll d = ext_gcd(b, a%b, y, x); //xにyの値を入れている
    y -= a/b * x;
    return d;
}

//素因数分解
vector<pair<ll,int>> factorize(ll n) {
    vector<pair<ll,int>> res;
    ll N = n;
    for (ll i = 2; i * i <= N; i++) {
        if (n % i != 0) continue;
        res.emplace_back(i,0);
        while (n % i == 0) {
            n /= i;
            res.back().second++;
        } 
    }
    if (n != 1) res.emplace_back(n,1);
    return res;
}

//階乗
ll factorial(int x) {
    if (x == 1) return 1;
    return x * factorial(x-1);
}

//エラストテネスの篩
int mx = 1e5;
vector<bool> prime(mx+1,true);
prime[1] = false;
for (int i = 2; i <= mx; i++) {
    if (prime[i]) {
        for (int j = 2*i; j <= mx; j += i) prime[j] = false;
    }
}

// nCr(v[n][r])(パスカルバージョン)
void comb(vvll &v) {
    rep(i,v.size()) {
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for (int k = 1; k < v.size(); k++) {
        for (int j = 1; j < k; j++) {
            v[k][j] = v[k-1][j-1] + v[k-1][j];
        }
    }
}