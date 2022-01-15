#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// fraction from https://github.com/nealwu/competitive-programming/blob/master/number_theory/fraction.cc
struct fraction {
    // TODO: set this to false if it's unnecessary and the time limit might be tight.
    // CHECK_OVERFLOW64 = true can run up to 2 times slower (particularly on CF).
    static const bool CHECK_OVERFLOW64 = false;

    // TODO: consider setting AUTO_REDUCE = false for faster code. In this case, remember to call reduce() at the end.
    static const bool AUTO_REDUCE = true;

    static int cross_sign(const fraction &a, const fraction &b) {
        if (CHECK_OVERFLOW64) {
            long double double_value = (long double) a.numer * b.denom - (long double) b.numer * a.denom;

            if (abs(double_value) > 1e18)
                return double_value > 0 ? +1 : -1;
        }

        uint64_t uint64_value = (uint64_t) a.numer * b.denom - (uint64_t) b.numer * a.denom;
        int64_t actual = int64_t(uint64_value);
        return (actual > 0) - (actual < 0);
    }

    int64_t numer, denom;

    fraction(int64_t n = 0, int64_t d = 1) : numer(n), denom(d) {
        check_denom();

        if (AUTO_REDUCE)
            reduce();
    }

    void check_denom() {
        if (denom < 0) {
            numer = -numer;
            denom = -denom;
        }
    }

    void reduce() {
        int64_t g = __gcd(abs(numer), denom);
        numer /= g;
        denom /= g;
    }

    bool is_integer() const {
        return denom == 1 || (!AUTO_REDUCE && denom != 0 && numer % denom == 0);
    }

    friend fraction operator+(const fraction &a, const fraction &b) {
        return fraction(a.numer * b.denom + b.numer * a.denom, a.denom * b.denom);
    }

    friend fraction operator-(const fraction &a, const fraction &b) {
        return fraction(a.numer * b.denom - b.numer * a.denom, a.denom * b.denom);
    }

    friend fraction operator*(const fraction &a, const fraction &b) {
        return fraction(a.numer * b.numer, a.denom * b.denom);
    }

    friend fraction operator/(const fraction &a, const fraction &b) {
        return fraction(a.numer * b.denom, a.denom * b.numer);
    }

    fraction& operator+=(const fraction &other) { return *this = *this + other; }
    fraction& operator-=(const fraction &other) { return *this = *this - other; }
    fraction& operator*=(const fraction &other) { return *this = *this * other; }
    fraction& operator/=(const fraction &other) { return *this = *this / other; }

    fraction& operator++() { numer += denom; return *this; }
    fraction& operator--() { numer -= denom; return *this; }

    fraction operator++(int) { fraction before = *this; ++*this; return before; }
    fraction operator--(int) { fraction before = *this; --*this; return before; }

    fraction operator-() const {
        return fraction(-numer, denom);
    }

    fraction inv() const {
        return fraction(denom, numer);
    }

    bool operator==(const fraction &other) const { return cross_sign(*this, other) == 0; }
    bool operator!=(const fraction &other) const { return cross_sign(*this, other) != 0; }
    bool operator<(const fraction &other) const { return cross_sign(*this, other) < 0; }
    bool operator>(const fraction &other) const { return cross_sign(*this, other) > 0; }
    bool operator<=(const fraction &other) const { return cross_sign(*this, other) <= 0; }
    bool operator>=(const fraction &other) const { return cross_sign(*this, other) >= 0; }

    explicit operator double() const {
        return double(numer) / double(denom);
    }

    explicit operator long double() const {
        return (long double) numer / (long double) denom;
    }

    friend fraction abs(const fraction &f) {
        return fraction(abs(f.numer), f.denom);
    }

    friend ostream& operator<<(ostream& out, const fraction &frac) {
        return out << frac.numer << '/' << frac.denom;
    }
};

template<typename T>
struct matrix {
    int R, C;
    vector<vector<T>> data;

    explicit matrix(int r = -1, int c = -1) : R(r), C(c) {
        if (r > 0 && c > 0)
            data.assign(r, vector<T>(c));
    }
    explicit matrix(const vector<vector<T>>& _data) {
        init(_data);
    }

    void init(const vector<vector<T>>& A) {
        data = A;
        R = int(data.size());
        C = data.empty() ? 0 : int(data[0].size());
    }

    vector<T>& operator[](int r) {
        // assert(0 <= 0 && r < R);
        return data[r]; 
    }
    const vector<T>& operator[](int r) const {
        // assert(0 <= 0 && r < R);
        return data[r];
    }

    bool empty() const {
        return R <= 0 || C <= 0;
    }

    matrix transposed() const {
        matrix trans(C, R);
        
        for (int r = 0; r < R; ++r)
            for (int c = 0; c < C; ++c)
                trans[c][r] = data[r][c];

        return trans;
    }

    matrix<T>& operator+=(const matrix<T>& other) {
        assert(R == other.R && C == other.C);

        for (int r = 0; r < R; ++r)
            for (int c = 0; c < C; ++c)
                data[r][c] += other[r][c];

        return *this;
    }
    matrix<T>& operator-=(const matrix<T>& other) {
        assert(R == other.R && C == other.C);

        for (int r = 0; r < R; ++r)
            for (int c = 0; c < C; ++c)
                data[r][c] -= other[r][c];

        return *this;
    }
    matrix<T>& operator*=(T k) {
        for (int r = 0; r < R; ++r)
            for (int c = 0; c < C; ++c)
                data[r][c] *= k;
        
        return *this;
    }

    friend matrix operator+(const matrix& a, const matrix& b) {
        return matrix(a) += b;
    }
    friend matrix operator-(const matrix& a, const matrix& b) {
        return matrix(a) -= b;
    }
    friend matrix operator*(const matrix& a, T k) {
        return matrix(a) *= k;
    }
    friend matrix operator*(T k, const matrix& a) {
        return a * k;
    }
    // a naive way to calculate a * b;
    friend matrix operator*(const matrix& a, const matrix& b) {
        assert(a.C == b.R);
        int R = a.R, C = b.C, S = b.R;
        matrix result(R, C);

        for (int r = 0; r < R; ++r)
            for (int s = 0; s < S; ++s) {
                T x = a[r][s];

                for (int c = 0; c < C; ++c)
                    result[r][c] += x * b[s][c];
            }

        return result;
    }

    friend ostream& operator<<(ostream& os, const matrix& M) {
        for (int r = 0; r < M.R; ++r)
            for (int c = 0; c < M.C; ++c)
                os << M[r][c] << (c < M.C - 1 ? ' ' : '\n');

        return os;
    }
    friend istream& operator>>(istream& is, matrix& M) {
        for (auto& row : M.data)
            for (auto& x : row)
                cin >> x;

        return is;
    }
};

template<typename T>
struct determinant : public matrix<T> {
public:
    using matrix<T>::R;
    using matrix<T>::C;
    using matrix<T>::data;

    explicit determinant(int n = -1) : matrix<T>(n, n) {}
    explicit determinant(const vector<vector<T>>& _data) : matrix<T>(_data) {
        assert(_data.size() == _data[0].size());
    }

    // returns a empty determinant when no solution.
    determinant inv() const {
        int N = R;
        determinant A(data);
        determinant ones(N);

        for (int i = 0; i < N; ++i)
            ones[i][i] = 1;

        for (int i = 0; i < N; ++i) {
            int piovt = i;

            for (int j = i + 1; j < N; ++j)
                if (abs(A[piovt][i]) < abs(A[j][i]))
                    piovt = j;

            if (piovt != i) {
                for (int c = i; c < N; ++c)
                    swap(A[i][c], A[piovt][c]);

                for (int c = 0; c < N; ++c)
                    swap(ones[i][c], ones[piovt][c]);
            }

            if (A[i][i] == 0)
                return determinant();

            for (int r = 0; r < N; ++r)
                if (r != i && A[r][i] != 0) {
                    T t = A[r][i] / A[i][i];

                    for (int c = i; c < N; ++c)
                        A[r][c] -= A[i][c] * t;

                    for (int c = 0; c < N; ++c)
                        ones[r][c] -= ones[i][c] * t;
                }

            T inv_ = 1 / A[i][i];

            for (int c = 0; c < N; ++c)
                A[i][c] = A[i][c] * inv_;
            
            for (int c = 0; c < N; ++c)
                ones[i][c] = ones[i][c] * inv_;
        }

        return determinant(ones);
    }

    // triangularize the matrix and returns the det of data
    T triangularize() {
        int N = R, rank = 0;
        T det = 1;

        for (int col = 0, row = 0; col < N && row < N; col++) {
            int piovt = row;
            
            for (int k = row; k < N; k++)
                if (data[k][col] > data[piovt][col])
                    piovt = k;
        
            if (data[piovt][col] == 0) {
                det = 0;
                continue;
            }
            
            if (piovt != row)
                for (int j = col; j < N; j++) {
                    swap(data[piovt][j], data[row][j]);                
                    data[row][j] *= -1; // kind of ..., you can remove it and rewrite todo.
                }

            det *= data[row][col]; // todo

            for (int i = 0; i < N; i++)
                if (i != row && data[i][col] != 0) {
                    T t = data[i][col] / data[row][col];
                    
                    for (int j = col; j < N; j++)
                        if (data[row][j] != 0)
                            data[i][j] -= data[row][j] * t;
                }

            row++;
            rank++;
        }
        
        return det;
    }

    T det() const {
        return determinant(*this).triangularize();
    }
};

using matrix_t = matrix<fraction>;
using det_t = determinant<fraction>;
// using matrix_t = matrix<mint>;
// using det_t = determinant<mint>;
// using matrix_t = matrix<double>;
// using det_t = determinant<double>;

const double EPS = 1e-9;

inline void show(const char* m) {
    cout << m;
}

int main() {
    while (true) {
        show("0. eixt\n");
        show("1. matrix operations\n");
        show("2. matrix inversion\n");
        show("3. determinant\n");
        show("4. triangularize matrix\n");
        show("5. transpose matrix\n");
        show("6. clear the screen\n");

        int op;
        cin >> op;

        switch (op) {
        case 1: {
            show("1. A+B\n");
            show("2. A-B\n");
            show("3. A*B\n");

            int mop;
            cin >> mop;
            
            show("enter the row and column of A: R C\n");
            int R, C;
            cin >> R >> C;
            matrix_t A(R, C);
            show("enter matrix A\n");
            cin >> A;

            if (mop == 3) {
                show("enter the row and column of B: R C\n");
                cin >> R >> C;
            }

            matrix_t B(R, C);
            show("enter matrix B\n");
            cin >> B;

            if (mop == 1) {
                show("A + B:\n");
                cout << A + B;
            } else if (mop == 2){
                show("A - B:\n");
                cout << A - B;
            } else {
                show("A * B:\n");
                cout << A * B;
            }
            break;
        }
        case 2: {
            show("enter the size of matrix: N\n");
            int N;
            cin >> N;
            det_t A(N);
            show("enter the matrix\n");
            cin >> A;
            det_t invA = A.inv();

            if (invA.empty()) {
                show("this matrix has no inversion matrix\n");
            } else {
                show("inv:\n");
                cout << invA;
            }

            break;
        }
        case 3: {
            show("enter the size of matrix: N\n");
            int N;
            cin >> N;
            det_t A(N);
            show("enter the matrix\n");
            cin >> A;
            show("det:\n");
            cout << A.det();
            break;
        }
        case 4: {
            show("enter the size of matrix: N\n");
            int N;
            cin >> N;
            det_t A(N);
            show("enter the matrix\n");
            cin >> A;
            A.triangularize();
            show("triangularized:\n");
            cout << A;
            break;
        }
        case 5: {
            show("enter the row and column of the matrix: R C\n");
            int R, C;
            cin >> R >> C;
            matrix_t A(R, C);
            show("enter the matrix\n");
            cin >> A;
            show("transposed:\n");
            cout << A.transposed();
            break;
        }
        case 6:
            // system("cls");
            break;
        default:
            show("enter the correct command\n");
            break;
        }

        cout << endl;
        
        if (op == 0)
            break;
    }
}