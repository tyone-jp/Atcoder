double EPS = 1e-10;

double add(double a, double b) {
    if (abs(a+b) < EPS*(abs(a)+abs(b))) return 0;
    return a+b;
}

struct P {
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y); {}
    P operator + (P p) {
        return P(add(x,p.x),add(y,p.y));
    }
    P operator - (P p) {
        return P(add(x,-p.x),add(y,-p.y));
    }
    P operator * (double d) {
        return P(x*d,y*d);
    }
    double dot(P p) {
        return add(x*p.x,y*p.y);
    }
    double det(P p) {
        return add(x*p.y,-y*p.x);
    }
};

// 線分p1-p2に点qがあるか
bool on_seg(P p1, P p2, P q) {
    return (p1-q).det(p2-q) == 0 && (p1-q).dot(p2-q) <= 0;
}

// 直線p1-p2と直線q1-q2の交点
P intersection(P p1, P p2, P q1, P q2) {
    return p1+(p2-p1)*((q2-q1).det(q1-p1)/(q2-q1).det(p2-p1));
}