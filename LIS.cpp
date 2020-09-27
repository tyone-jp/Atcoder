int LIS(vector<int> &a) {
    vector<int> dp;
    for (int x : a) {
        auto itr = lower_bound(dp.begin(),dp.end(),x);
        if (itr != dp.end()) *itr = x;
        else dp.push_back(x);
    }
    return dp.size();
}