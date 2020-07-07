//sとs[i:]の最長接頭辞長
vector<int> z_algorithm(string &s) {
    vector<int> res(s.size());
    res[0] = s.size();
    int i = 1, j = 0;
    while (i < (int)s.size()) {
        while (i+j < (int)s.size() && s[j] == s[i+j]) j++;
        res[i] = j;

        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (k < j && k + res[k] < j) {
            res[i+k] = res[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return res;
}