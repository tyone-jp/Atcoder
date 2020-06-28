// "a b c" -> {a,b,c}
vector<string> split(string in) {
    vector<string> res;
    stringstream ss(in);
    string s;
    while (ss >> s) res.push_back(s);
    return res;
}