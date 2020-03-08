//素数の判定
bool is_prime(ll a) {
    bool ok = true;
    if (a == 1) return false;
    if (a == 2) return true;
    else {
        rep(i,sqrt(a)) {
            if (a % (i+2) == 0) ok = false;
        }
        return ok;
    }
}
//最大公約数と最小公倍数
ll gcd(ll a, ll b) {return(b?gcd(b,a%b):a)}
ll lcm(ll a, ll b) {return(a/gcd(a,b)*b)}