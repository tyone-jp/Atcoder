//最大公約数と最小公倍数
ll gcd(ll a, ll b) {return(b ? gcd(b, a % b) : a);}
ll lcm(ll a, ll b) {return(a / gcd(a, b) * b);}

//拡張ユークリッド(返り値はgcd(a,b))
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x); //xにyの値を入れている
    y -= a / b * x;
    return d;
}

// a * x = 1(mod m)
ll mod_inverse(ll a, ll m) {
    ll x, y;
    ext_gcd(a, m, x, y);
    return (m + x % m) % m;
}

//階乗
ll factorial(int x) {
    if (x == 1) return 1;
    return x * factorial(x-1);
}

//重複組み合わせの列挙
vector<int> buf;
void dfs(int i, const int size, const int range_start, const int range_end) {
    if (i == size) {
        //処理
    } else {
        for (int j = range_start; j <= range_end; j++) {
            buf[i] = j;
            dfs(i+1,size,range_start,range_end);
        }
    }
}