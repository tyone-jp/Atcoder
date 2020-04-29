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

//mod(1e9+7)
const int mod = 1e9+7;
struct mint {
    ll x;
    mint(ll x = 0) : x(x % mod){}
    mint &operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator-=(const mint a) {
        if ((x += mod - a.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator*=(const mint a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint operator+(const mint a) const {
        mint res(*this);
        return res += a;
    }
    mint operator-(const mint a) const {
        mint res(*this);
        return res -= a;
    }
    mint operator*(const mint a) const {
        mint res(*this);
        return res *= a;
    }
};

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

// nCr
vll fac(MAX), finv(MAX), inv(MAX);
void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i <= MAX; i++) {
        fac[i] = fac[i-1] * i % mod;
        inv[i] = mod - inv[mod%i] * (mod/i) % mod;
        finv[i] = finv[i-1] * inv[i] % mod;
    }
}

ll com(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n-k] % mod) % mod;
}