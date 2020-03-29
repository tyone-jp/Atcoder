//chmin,chmax
template<class T> bool chmin(T &a, T b) {if(a>b) {a=b;return 1;}return 0;}
template<class T> bool chmax(T &a, T b) {if(a<b) {a=b;return 1;}return 0;}

//all(x)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()