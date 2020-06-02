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

//階乗
ll factorial(int x) {
    if (x == 1) return 1;
    return x * factorial(x-1);
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