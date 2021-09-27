
struct interval {
    int start, end;
    static const int INF = 0x3f3f3f3f;

    interval(int _start = -INF, int _end = INF) : start(_start), end(_end) {}

    inline int length() const {
        return end - start + 1;
    }

    bool operator<(const interval& rhs) const {
        if (start != rhs.start) {
            return start < rhs.start;
        }
        return end < rhs.end;
    }

    inline friend interval intersection(const interval& A, const interval& B) {
        return interval(max(A.start, B.start), min(A.end, B.end));
    }

    inline friend int union_length(const interval& A, const interval& B) {
        int total = A.length() + B.length();
        return min(total, max(A.end, B.end) - min(A.start, B.start) + 1);
    }

    inline friend int intersect_length(const interval& A, const interval& B) {
        return max(intersection(A, B).length(), 0);
    }

    friend ostream& operator<<(ostream& os, interval& x) {
        os << x.start << ' ' << x.end;
        return os;
    }

    friend istream& operator>>(istream& is, interval& x) {
        is >> x.start >> x.end;
        return is;
    }

};
