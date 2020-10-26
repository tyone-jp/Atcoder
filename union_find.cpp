// union-find
struct union_find {
    vector<int> dat;

    union_find(int size) {dat.resize(size,-1);}

    int find(int x) {
        if (dat[x] < 0) {return x;}
        return dat[x] = find(dat[x]);
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) {return false;}
        if (dat[x] > dat[y]) swap(x,y);
        dat[x] += dat[y];
        dat[y] = x;
        return true;
    }

    int size(int x) {return -dat[find(x)];}
};