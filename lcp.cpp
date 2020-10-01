struct SuffixArray {
    string S;
    int N;
    vint sa;
    SuffixArray(string str_in) : S(str_in), N((int)str_in.size()) {
        str_in += "$";
        vint str(N + 1);
        for (int i = 0; i < N + 1; i++) str[i] = str_in[i] - '$';
        sa = sa_is(str, 128);
    }
    // kは文字の種類数
    vint sa_is(const vint &str, const int k) {
        const int n = str.size();

        vector<bool> is_S(n, false); is_S[n-1] = true;
        vector<bool> is_LMS(n);
        vint LMSs;
        for (int i = n - 2; i >= 0; i--) {
            is_S[i] = str[i] < str[i + 1] || (str[i] == str[i + 1] && is_S[i + 1]);
        }
        for (int i = 1; i < n; i++) {
            if (is_S[i] && !is_S[i-1]) {
                is_LMS[i] = true;
                LMSs.push_back(i);
            }
        }
        vint pseudo_sa = induced_sort(str, LMSs, is_S, k);
        vint orderedLMSs((int)LMSs.size());
        int index = 0;
        for (int x : pseudo_sa) {
            if (is_LMS[x]) orderedLMSs[index++] = x;
        }
        pseudo_sa[orderedLMSs[0]] = 0;
        int rank = 0;
        if (orderedLMSs.size() > 1) pseudo_sa[orderedLMSs[1]] = ++rank;
        for (int i = 1; i < (int)orderedLMSs.size() - 1; i++) {
            bool is_diff = false;
            for (int j = 0; j < n; j++) {
                int p = orderedLMSs[i] + j;
                int q = orderedLMSs[i + 1] + j;
                if (str[p] != str[q] || is_LMS[p] != is_LMS[q]) {
                    is_diff = true;
                    break;
                }
                if (j > 0 && is_LMS[p]) break;
            }
            pseudo_sa[orderedLMSs[i + 1]] = is_diff ? ++rank : rank;
        }
        vint new_str(LMSs.size());
        index = 0;
        for (int i = 0; i < n; i++) {
            if (is_LMS[i]) new_str[index++] = pseudo_sa[i];
        }
        vint LMS_sa;
        if (rank + 1 == (int)LMSs.size()) {
            LMS_sa = orderedLMSs;
        } else {
            LMS_sa = sa_is(new_str, rank + 1);
            for (int &x : LMS_sa) x = LMSs[x];
        }
        return induced_sort(str, LMS_sa, is_S, k);
    }

    vint induced_sort(const vint &str, const vint &LMSs, const vector<bool> &is_S, const int k) {
        int n = str.size();
        vint buckets(n);
        vint chars(k + 1);  //各bucketのはじめのindex;
        for (int c : str) chars[c + 1]++;
        for (int i = 0; i < k; i++) chars[i + 1] += chars[i];
        vint count(k, 0);
        for (int i = LMSs.size() - 1; i >= 0; i--) {
            int c = str[LMSs[i]];
            buckets[chars[c + 1] - 1 - count[c]++] = LMSs[i];
        }
        count = vint(k, 0);
        for (int i = 0; i < n; i++) {
            // i - 1　がLならbucketに前から詰める
            if (buckets[i] == 0 || is_S[buckets[i] - 1]) continue;
            int c = str[buckets[i] - 1];
            buckets[chars[c] + count[c]++] = buckets[i] - 1;
        }
        count = vint(k, 0);
        for (int i = n - 1; i >= 0; i--) {
            // i - 1 がSならbucketに後ろから詰める
            if (buckets[i] == 0 || !is_S[buckets[i] - 1]) continue;
            int c = str[buckets[i] - 1];
            buckets[chars[c + 1] - 1 - count[c]++] = buckets[i] - 1;
        }
        return buckets;
    }
};

struct lcp_array {
    string S;
    vint sa;
    vint lcp;
    vint rank;
    lcp_array(string S_in) : S(S_in), lcp(S_in.size()), rank(S_in.size() + 1) {
        sa = SuffixArray(S_in).sa;
        construct_lcp();
    }
    void construct_lcp() {
        int n = S.size();
        for (int i = 0; i <= n; i++) rank[sa[i]] = i;
        int h = 0;
        lcp[0] = 0;
        for (int i = 0; i < n; i++) {
            int j = sa[rank[i] - 1];
            if (h > 0) h--;
            for (; j + h < n && i + h < n; h++) {
                if (S[j + h] != S[i + h]) break;
            }
            lcp[rank[i] - 1] = h;
        }
    }
};