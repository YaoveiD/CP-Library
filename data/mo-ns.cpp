#include <bits/stdc++.h>
using namespace std;

#define sz(c) int(c.size())
#define all(c) c.begin(), c.end()

struct mo_query {
    int start, end, index, block;

    bool operator<(const mo_query &other) const {
        if (other.block != block)
            return block < other.block;

        return block % 2 == 0 ? end < other.end : end > other.end;
    }
};

namespace mo {
    using mo_value = int;
    using mo_answer = int;
    const int N_MAX = 100005;
    int n;
    mo_value values[N_MAX];
    int freq[N_MAX];
    int fcnt[N_MAX];
    int start, end;
    mo_answer answer;

    inline void add_left(int index) {
        int x = values[index];
        fcnt[freq[x]]--;
        freq[x]++;
        fcnt[freq[x]]++;

        if (fcnt[answer+1] > 0)
            answer++;
    }

    inline void add_right(int index) {
        add_left(index);
    }

    inline void remove_left(int index) {
        int x = values[index];
        fcnt[freq[x]]--;
        freq[x]--;
        fcnt[freq[x]]++;

        if (fcnt[answer] == 0)
            answer--;
    }

    inline void remove_right(int index) {
        remove_left(index);
    }

    void update_state(int qstart, int qend) {
        if (max(start, qstart) >= min(end, qend)) {
            for (int i = start; i < end; ++i)
                remove_left(i);
            for (int i = qstart; i < qend; ++i)
                add_right(i);
            return;
        }

        for (int i = start - 1; i >= qstart; --i)
            add_left(i);
        for (int i = end; i < qend; ++i)
            add_right(i);
        for (int i = start; i < qstart; ++i)
            remove_right(i);
        for (int i = end - 1; i >= qend; --i)
            remove_left(i);
    }

    void init(const vector<int> &A) {
        n = int(A.size());
        copy(A.begin(), A.end(), values);
        start = end = 0;
    }

    vector<mo_answer> solve(vector<mo_query> queries) {
        int block_size = int(1.5 * n / sqrt(max(int(queries.size()), 1)) + 1);

        for (int i = 0; i < int(queries.size()); i++) {
            queries[i].index = i;
            queries[i].block = queries[i].start / block_size;
        }

        sort(queries.begin(), queries.end());
        vector<mo_answer> answers(queries.size());

        for (mo_query &q : queries) {
            update_state(q.start, q.end);
            answers[q.index] = answer;
            start = q.start; end = q.end;
        }

        // clear
        while (start < end)
            remove_left(start++);

        return answers;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);

    for (int &a : A)
        cin >> a;

    vector<int> sorted(A);
    sort(all(sorted));
    sorted.erase(unique(all(sorted)), sorted.end());

    for (int &a : A)
        a = int(lower_bound(all(sorted), a) - sorted.begin());

    vector<mo_query> queries(Q);
    
    for (int q = 0; q < Q; ++q) {
        cin >> queries[q].start >> queries[q].end;
        queries[q].start--;
    }

    mo::init(A);
    vector<mo::mo_answer> answers = mo::solve(queries);

    for (int answer : answers)
        cout << answer << '\n';
}
