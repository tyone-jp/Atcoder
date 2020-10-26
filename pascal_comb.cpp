struct pascal_comb {
    vector<vector<long long>> dat;
    pascal_comb(int s) : dat(s + 1, vector<long long>(s + 1)) {
        rep(i,s+1) {
            dat[i][0] = 1;
            dat[i][i] = 1;
        }
        for (int k = 1; k < s + 1; k++) {
            for (int j = 1; j < k; j++) {
                dat[k][j] = dat[k - 1][j - 1] + dat[k - 1][j];
            }
        }
    }
    long long operator() (int a, int b) {
        if (b < 0 || a < b) return 0;
        return dat[a][b];
    }
};