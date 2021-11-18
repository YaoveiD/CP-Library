#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// // https://github.com/nealwu/competitive-programming/tree/master/mod

// template<int md>
// class _mod_int {
// public:
//   int val;

//   _mod_int(int64_t v = 0) {
//     if (v < 0)
//       v = v % md + md;
//     if (v >= md)
//       v %= md;
//     val = int(v);
//   }

//   _mod_int(int v) : _mod_int(int64_t(v)) {}
//   _mod_int(unsigned v) : _mod_int(int64_t(v)) {}

//   static int inv_mod(int a, int m = md) {
//     // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
//     int g = m, r = a, x = 0, y = 1;

//     while (r != 0) {
//       int q = g / r;
//       g %= r;
//       swap(g, r);
//       x -= q * y;
//       swap(x, y);
//     }

//     return x < 0 ? x + m : x;
//   }

//   explicit operator int() const { return val; }
//   explicit operator unsigned() const { return val; }
//   explicit operator int64_t() const { return val; }

//   _mod_int& operator+=(const _mod_int &other) {
//     val -= md - other.val;
//     if (val < 0)
//       val += md;
//     return *this;
//   }
//   _mod_int& operator-=(const _mod_int &other) {
//     val -= other.val;
//     if (val < 0)
//       val += md;
//     return *this;
//   }
//   _mod_int &operator*=(const _mod_int &other) {
//     val = int64_t(val) * other.val % md;
//     return *this;
//   }
//   _mod_int &operator/=(const _mod_int &other) { return *this *= other.inv(); }

//   friend _mod_int operator+(const _mod_int &a, const _mod_int &b) {
//     return _mod_int(a) += b;
//   }
//   friend _mod_int operator-(const _mod_int &a, const _mod_int &b) {
//     return _mod_int(a) -= b;
//   }
//   friend _mod_int operator*(const _mod_int &a, const _mod_int &b) {
//     return _mod_int(a) *= b;
//   }
//   friend _mod_int operator/(const _mod_int &a, const _mod_int &b) {
//     return _mod_int(a) /= b;
//   }

//   _mod_int& operator++() {
//     val = val == md - 1 ? 0 : val + 1;
//     return *this;
//   }
//   _mod_int& operator--() {
//     val = val == 0 ? md - 1 : val - 1;
//     return *this;
//   }

//   _mod_int operator-() const { return val == 0 ? 0 : md - val; }

//   friend bool operator==(const _mod_int &a, const _mod_int &b) {
//     return a.val == b.val;
//   }
//   friend bool operator!=(const _mod_int &a, const _mod_int &b) {
//     return a.val != b.val;
//   }
//   friend bool operator<(const _mod_int &a, const _mod_int &b) {
//     return a.val < b.val;
//   }

//   _mod_int inv() const { return inv_mod(val); }

//   _mod_int pow(int64_t p) const {
//     if (p < 0)
//       return inv().pow(-p);

//     _mod_int a = *this, result = 1;

//     while (p > 0) {
//       if (p & 1)
//         result *= a;

//       p >>= 1;

//       if (p > 0)
//         a *= a;
//     }

//     return result;
//   }

//   friend string to_string(const _mod_int& m) {
//     return to_string(m.val);
//   }

//   friend ostream& operator<<(ostream& os, const _mod_int& m) {
//     return os << m.val;
//   }
// };

// const int MOD = (int) 1e9 + 7;
// using mint = _mod_int<MOD>;

class fraction {
private:
    int64_t num, denom;

public:
    fraction(int64_t v = 0) : num(v), denom(1) {}
    fraction(int v) : fraction(int64_t(v)) {}
    fraction(int64_t a, int64_t b) : num(a), denom(b) {
        assert(b != 0);
        norm();
    }

    static int64_t gcd(int64_t a, int64_t b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    void norm() {
        int64_t G = gcd(num, denom);
        num /= G;
        denom /= G;
    }

    explicit operator double() const { return double(num) / denom; }

    fraction operator-() const { return fraction(-num, denom); }
    fraction inv() const { return fraction(denom, num); }

    // consider rewrite this if overflow
    fraction& operator+=(const fraction& other) {
        int64_t G = gcd(denom, other.denom);
        num = other.denom / G * num + denom / G * other.num;
        denom = denom / G * other.denom;
        norm();
        return *this;
    }
    fraction& operator-=(const fraction& other) {
        *this += -other;
        norm();
        return *this;
    }
    fraction& operator*=(const fraction& other) {
        int64_t G1 = gcd(num, other.denom);
        int64_t G2 = gcd(other.num, denom);
        num = (num / G1) * (other.num / G2);
        denom = (denom / G2) * (other.denom / G1);
        norm();
        return *this;
    }
    fraction& operator/=(const fraction& other) {
        assert(!other.zero());
        *this *= other.inv();
        norm();
        return *this;
    }

    friend fraction operator+(const fraction& a, const fraction& b) {
        return fraction(a) += b;
    }
    friend fraction operator-(const fraction& a, const fraction& b) {
        return fraction(a) -= b;
    }
    friend fraction operator*(const fraction& a, const fraction& b) {
        return fraction(a) *= b;
    }
    friend fraction operator/(const fraction& a, const fraction& b) {
        return fraction(a) /= b;
    }

    bool zero() const { return num == 0; }
    bool negtive() const { return num * denom < 0; } // overflow?
    bool positive() const { return num * denom > 0; }
    
    friend fraction abs(const fraction& a) {
        return a.negtive() ? -a : a;
    }
    friend bool operator==(const fraction& a, const fraction& b) {
        return (a - b).zero();
    }
    friend bool operator!=(const fraction& a, const fraction& b) {
        return !(a - b).zero();
    }
    friend bool operator<(const fraction& a, const fraction& b) {
        return (a - b).negtive();        
    }
    friend bool operator>(const fraction& a, const fraction& b) {
        return (a - b).positive();
    }
    friend bool operator<=(const fraction&a , const fraction& b) {
        return !(a > b);
    }
    friend bool operator>=(const fraction&a , const fraction& b) {
        return !(a < b);
    }

    // kind of complicated.
    friend ostream& operator<<(ostream& os, const fraction& f) {
        if (f.negtive())
            os << '-';

        if (f.denom == 1) {
            os << abs(f.num);
        } else {
            os << abs(f.num) << '/' << abs(f.denom);
        }

        return os;
    }

    friend istream& operator>>(istream& is, fraction& f) {
        string value;
        cin >> value;
        int64_t nums[2] = {0, 0};
        bool negtive[2] = {false, false};
        int ptr = 0;

        for (char c : value)
            if (c == '/') {
                ptr++;
            } else {
                if (c == '-')
                    negtive[ptr] = true;
                else
                    nums[ptr] = nums[ptr] * 10 + c - '0';
            }

        if (negtive[0])
            nums[0] = -nums[0];

        if (ptr != 1)
            nums[1] = 1;
        else if (negtive[1])
            nums[1] = -nums[1];

        f = fraction(nums[0], nums[1]);
        return is;
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