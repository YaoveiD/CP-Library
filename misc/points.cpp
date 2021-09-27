// https://github.com/ecnerwala/cp-book/blob/master/src/geometry/point.hpp

template <typename T> struct Point {
public:
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x_, T y_) : x(x_), y(y_) {}
    template <typename U> explicit Point(const Point<U>& p) : x(p.x), y(p.y) {}
    Point(const std::pair<T, T>& p) : x(p.first), y(p.second) {}
    explicit operator std::pair<T, T> () const { return std::pair<T, T>(x, y); }

    friend std::ostream& operator << (std::ostream& o, const Point& p) { return o <<  p.x << ' ' << p.y <<; }
    friend std::istream& operator >> (std::istream& i, Point& p) { return i >> p.x >> p.y; }
    friend bool operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const Point& a, const Point& b) { return !(a==b); }

    Point operator+() const { return Point(+x, +y); }
    Point operator-() const { return Point(-x, -y); }

    Point& operator+=(const Point& p) { x += p.x, y += p.y; return *this; }
    Point& operator-=(const Point& p) { x -= p.x, y -= p.y; return *this; }
    Point& operator*=(const T& t) { x *= t, y *= t; return *this; }
    Point& operator/=(const T& t) { x /= t, y /= t; return *this; }

    friend Point operator+(const Point& a, const Point& b) { return Point(a.x+b.x, a.y+b.y); }
    friend Point operator-(const Point& a, const Point& b) { return Point(a.x-b.x, a.y-b.y); }
    friend Point operator*(const Point& a, const T& t) { return Point(a.x*t, a.y*t); }
    friend Point operator*(const T& t ,const Point& a) { return Point(t*a.x, t*a.y); }
    friend Point operator/(const Point& a, const T& t) { return Point(a.x/t, a.y/t); }

    T dist2() const { return x * x + y * y; }
    auto dist() const { return std::sqrt(dist2()); }
    Point unit() const { return *this / this->dist(); }
    auto angle() const { return std::atan2(y, x); }

    T int_norm() const { return __gcd(x,y); }
    Point int_unit() const { if (!x && !y) return *this; return *this / this->int_norm(); }

    // Convenient free-functions, mostly for generic interop
    friend auto norm(const Point& a) { return a.dist2(); }
    friend auto abs(const Point& a) { return a.dist(); }
    friend auto unit(const Point& a) { return a.unit(); }
    friend auto arg(const Point& a) { return a.angle(); }
    friend auto int_norm(const Point& a) { return a.int_norm(); }
    friend auto int_unit(const Point& a) { return a.int_unit(); }

    Point perp_cw() const { return Point(y, -x); }
    Point perp_ccw() const { return Point(-y, x); }

    friend T dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
    friend T cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
    friend T cross3(const Point& a, const Point& b, const Point& c) { return cross(b-a, c-a); }

    // Complex numbers and rotation
    friend Point conj(const Point& a) { return Point(a.x, -a.y); }

    // Returns conj(a) * b
    friend Point dot_cross(const Point& a, const Point& b) { return Point(dot(a, b), cross(a, b)); }
    friend Point cmul(const Point& a, const Point& b) { return dot_cross(conj(a), b); }
    friend Point cdiv(const Point& a, const Point& b) { return dot_cross(b, a) / b.norm(); }

    // Must be a unit vector; otherwise multiplies the result by abs(u)
    Point rotate(const Point& u) const { return dot_cross(conj(u), *this); }
    Point unrotate(const Point& u) const { return dot_cross(u, *this); }

    friend bool same_dir(const Point& a, const Point& b) { return cross(a,b) == 0 && dot(a,b) > 0; }

    // check if 180 <= s..t < 360
    friend bool is_reflex(const Point& a, const Point& b) { auto c = cross(a,b); return c ? (c < 0) : (dot(a, b) < 0); }

    // operator < (s,t) for angles in [base,base+2pi)
    friend bool angle_less(const Point& base, const Point& s, const Point& t) {
        int r = is_reflex(base, s) - is_reflex(base, t);
        return r ? (r < 0) : (0 < cross(s, t));
    }

    friend auto angle_cmp(const Point& base) {
        return [base](const Point& s, const Point& t) { return angle_less(base, s, t); };
    }
    friend auto angle_cmp_center(const Point& center, const Point& dir) {
        return [center, dir](const Point& s, const Point& t) -> bool { return angle_less(dir, s-center, t-center); };
    }

    // is p in [s,t] taken ccw? 1/0/-1 for in/border/out
    friend int angle_between(const Point& s, const Point& t, const Point& p) {
        if (same_dir(p, s) || same_dir(p, t)) return 0;
        return angle_less(s, p, t) ? 1 : -1;
    }
};

// https://codingcompetitions.withgoogle.com/kickstart/submissions/0000000000435bae/bmVhbF93dQ
// CHECK_OVERFLOW64 = true can run up to 2 times slower (particularly on CF).
const bool CHECK_OVERFLOW64 = false;

using dist_t = long double;

struct point {
    int64_t x, y;

    point() : x(0), y(0) {}

    point(int64_t _x, int64_t _y) : x(_x), y(_y) {}

    point& operator+=(const point &other) { x += other.x; y += other.y; return *this; }
    point& operator-=(const point &other) { x -= other.x; y -= other.y; return *this; }
    point& operator*=(int64_t mult) { x *= mult; y *= mult; return *this; }

    point operator+(const point &other) const { return point(*this) += other; }
    point operator-(const point &other) const { return point(*this) -= other; }
    point operator*(int64_t mult) const { return point(*this) *= mult; }

    bool operator==(const point &other) const { return x == other.x && y == other.y; }
    bool operator!=(const point &other) const { return !(*this == other); }

    point operator-() const { return point(-x, -y); }
    point rotate90() const { return point(-y, x); }

    int64_t norm() const {
        return (int64_t) x * x + (int64_t) y * y;
    }

    dist_t dist() const {
        return sqrt(dist_t(norm()));
    }

    bool top_half() const {
        return y > 0 || (y == 0 && x > 0);
    }

    friend ostream& operator<<(ostream &os, const point &p) {
        return os << '(' << p.x << ", " << p.y << ')';
    }
};

int64_t cross(const point &a, const point &b) {
    return (int64_t) a.x * b.y - (int64_t) b.x * a.y;
}

int64_t dot(const point &a, const point &b) {
    return (int64_t) a.x * b.x + (int64_t) a.y * b.y;
}

int cross_sign(const point &a, const point &b) {
    if (CHECK_OVERFLOW64) {
        long double double_value = (long double) a.x * b.y - (long double) b.x * a.y;

        if (abs(double_value) > 1e18)
            return double_value > 0 ? +1 : -1;
    }

    uint64_t uint64_value = (uint64_t) a.x * b.y - (uint64_t) b.x * a.y;
    int64_t actual = int64_t(uint64_value);
    return (actual > 0) - (actual < 0);
}

bool left_turn_strict(const point &a, const point &b, const point &c) {
    return cross_sign(b - a, c - a) > 0;
}

bool left_turn_lenient(const point &a, const point &b, const point &c) {
    return cross_sign(b - a, c - a) >= 0;
}

bool collinear(const point &a, const point &b, const point &c) {
    return cross_sign(b - a, c - a) == 0;
}

// Returns twice the signed area formed by three points in a triangle. Positive when a -> b -> c is a left turn.
int64_t area_signed_2x(const point &a, const point &b, const point &c) {
    return cross(b - a, c - a);
}

dist_t distance_to_line(const point &p, const point &a, const point &b) {
    assert(a != b);
    return dist_t(abs(area_signed_2x(p, a, b))) / (a - b).dist();
}

int64_t manhattan_dist(const point &a, const point &b) {
    return (int64_t) abs(a.x - b.x) + abs(a.y - b.y);
}

int64_t infinity_norm_dist(const point &a, const point &b) {
    return max(abs(a.x - b.x), abs(a.y - b.y));
}

// Sort in increasing order of y, with ties broken in increasing order of x.
bool yx_compare(const point &a, const point &b) {
    return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}

// Sort in increasing order of angle to the x-axis.
bool angle_compare(const point &a, const point &b) {
    if (a.top_half() ^ b.top_half())
        return a.top_half();

    return cross_sign(a, b) > 0;
}