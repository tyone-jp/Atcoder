//最長部分列長さ
int lcs(string s, string t) {
    int n_s = s.size();
    int n_t = t.size();
    vvint dp(n_s+1,vint(n_t+1,0));
    REP(i,n_s+1)REP(j,n_t+1) {
        if (s[i-1] == t[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
        else {
            chmax(dp[i][j],max(dp[i-1][j],dp[i][j-1]));
        }
    }
    return dp[n_s][n_t];
}