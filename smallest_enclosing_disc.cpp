//最小包含円(P(中心の座標、半径の２乗),O(N))
template<class iter>
pair<complex<double>,float> sed(iter left, iter right, int seed = 1333) {
    const int n = right - left;
    const double eps = 1e-6;

    assert(n >= 1);
    if (n == 1) return {*left,float(0)};
    
    mt19937 mt(seed);
    shuffle(left,right,mt);

    iter ps = left;
    using CD = complex<double>;
    using circle = pair<CD,double>;

    auto cross = [](const CD &a, const CD &b) -> double {
        return a.real()*b.imag()-b.real()*a.imag();
    };

    auto make_circle_3 = [&](const CD &a, const CD &b, const CD &c) -> circle {
        double A = norm(b-c), B = norm(a-c), C = norm(a-b), S = cross(b-a,c-a);
        CD p = (A*(B+C-A)*a + B*(C+A-B)*b + C*(A+B-C)*c) / (4*S*S);
        double r2 = norm(p-a);
        return {p,r2};
    };

    auto make_circle_2 = [](const CD &a, const CD &b) -> circle {
        CD c = (a+b)/(double)(2);
        double r2 = norm(c-a);
        return {c,r2};
    };

    auto in_circle = [&](const CD &a, const circle &c) -> bool {
        return norm(a-c.first) <= c.second + eps;
    };

    circle c = make_circle_2(ps[0],ps[1]);
    for (int i = 2; i < n; i++) {
        if (!in_circle(ps[i],c)) {
            c = make_circle_2(ps[i],ps[0]);
            for (int j = 1; j < i; j++) {
                if (!in_circle(ps[j],c)) {
                    c = make_circle_2(ps[i],ps[j]);
                    for (int k = 0; k < j; k++) {
                        if (!in_circle(ps[k],c)) {
                            c = make_circle_3(ps[i],ps[j],ps[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}