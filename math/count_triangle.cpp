
// Counts x, y >= 0 such that Ax + By <= C. Requires A, B > 0. Runs in log time.
// Also representable as sum_{0 <= x <= C / A} floor((C - Ax) / B + 1).
// See "A Simple Algorithm for Lattice Point Counting in Rational Polygons" by Hiroki Yanagisawa.
int64_t count_triangle(int64_t A, int64_t B, int64_t C) {
    if (C < 0) return 0;
    if (A < B) swap(A, B);
    int64_t m = C / A;
    int64_t h = (C - m * A) / B + 1;
    int64_t k = A / B;
    return m * (m + 1) / 2 * k + (m + 1) * h + count_triangle(B, A - k * B, C - B * (k * m + h));
}

// Computes the sum A / M + (A + D) / M + ... + (A + (N - 1) * D) / M, all floored.
int64_t arithmetic_floor_sum(int64_t A, int64_t D, int64_t N, int64_t M) {
    if (D == 0) return N * (A / M);
    return count_triangle(D, M, A + (N - 1) * D) - count_triangle(D, M, A - D) - N;
}