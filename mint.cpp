const int mod = 1e9+7;
struct mint {
    ll x;
    mint (ll x = 0) : x((x%mod+mod)%mod) {}
    mint operator -() const {return mint(-x);}
    mint& operator +=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator -=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator *=(const mint a) {(x *= a.x) % mod; return *this;}
    mint operator +(const mint a) const {return mint(*this) += a;}
    mint operator -(const mint a) const {return mint(*this) -= a;}
    mint operator *(const mint a) const {return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }
    mint inv() const {return pow(mod-2);}
    mint operator /=(const mint a) {return *this *= a.inv();}
    mint operator /(const mint a) {return mint(*this) /= a;}
};
istream& operator >>(istream &is, const mint &a) {return is >> a.x;}
ostream& operator <<(ostream &os, const mint &a) {return os << a.x;}