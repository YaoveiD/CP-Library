// soruce : https://chenshouao.github.io/mkdocs/pages/Algorithm/math/CircleCrossArea.html
// 利用余弦定理解三角形，时间复杂度O(1)。可将面积交转换为面积并。
namespace Circle{
    const double PI = acos(-1);
    struct Round {
        double x, y;
        double r;
        double area() {
            return PI * r * r;
        }
    } R[2];
    double dis(Round a, Round b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
    double get(Round a, Round b) {
        double d = dis(a, b);
        if (d >= a.r + b.r)
            return 0;
        if (d <= fabs(a.r - b.r)) {
            double r = a.r < b.r ? a.r : b.r;
            return PI * r * r;
        }
        double ang1 = acos((a.r * a.r + d * d - b.r * b.r) / 2. / a.r / d);
        double ang2 = acos((b.r * b.r + d * d - a.r * a.r) / 2. / b.r / d);
        double ret = ang1 * a.r * a.r + ang2 * b.r * b.r - d * a.r * sin(ang1);
        return ret;
    }
}
