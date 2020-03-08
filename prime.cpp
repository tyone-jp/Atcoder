//素数の判定
bool is_prime(ll a) {
    bool ok = true;
    if (a == 2) return ok;
    else {
        rep(i,sqrt(a)) {
            if (a % (i+2) == 0) ok = false;
        }
        return ok;
    }
}