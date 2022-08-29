/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */

void add(int ind, int end) {} // add a[ind] (end = 0 or 1)
void del(int ind, int end) {} // remove a[ind]
ans_t calc() {} // compute current answer

// queries are [inclusive, exclusive)
std::vector<ans_t> mo(const std::vector<std::pair<int, int>> &Q) {
    int L = 0, R = 0, blk = 350; // ~N/sqrt(Q)
    std::vector<int> s(Q.size());
    std::vector<ans_t> res(Q.size());
#define K(x) make_pair(x.first/blk, x.second ^ -(x.first/blk & 1))
    iota(s.begin(), s.end(), 0);
    sort(s.begin(), s.end(), [&](int a, int b){ return K(Q[a]) < K(Q[b]); });
    for (int qi : s) {
        auto &q = Q[qi];
        while (L > q.first) add(--L, 0);
        while (R < q.second) add(R++, 1);
        while (L < q.first) del(L++, 0);
        while (R > q.second) del(--R, 1);
        res[qi] = calc();
    }
    return res;
}
