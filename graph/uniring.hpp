// verfication : https://leetcode-cn.com/submissions/detail/254471413/
struct uniring {
    int n;
    std::vector<int> next;
    std::vector<std::vector<int>> cycles;
    std::vector<int> cycle_size;
    std::vector<int> start_max; // longest path start from node. Note: including node
    std::vector<int> end_max; // longest path end with node. Note: not include cycle node, but including node itself.

    uniring(int _n = -1) {
        if (_n != -1)
            init(_n);
    }

    uniring(std::vector<int>& _next) : n(_next.size()), next(_next) {}

    void init(int _n) {
        n = _n;
        next.assign(n, -1);
    }

    void add_edge(int a, int b) {
        next[a] = b;
    }

    void process(bool need_start = false, bool need_end = false) {
        std::vector<int> indeg(n);
        
        for (int node : next)
            if (node != -1)
                indeg[node]++;

        std::vector<int> que;

        for (int node = 0; node < n; ++node)
            if (indeg[node] == 0)
                que.push_back(node);

        for (int i = 0; i < int(que.size()); ++i) {
            int node = que[i];
            int to = next[node];

            if (to != -1 && --indeg[to] == 0)
                que.push_back(to);
        }

        cycle_size.assign(n, 0);

        for (int node = 0; node < n; ++node)
            if (indeg[node] > 0 && cycle_size[node] == 0) {
                int s = 1;

                for (int to = next[node]; to != node; to = next[to])
                    s++;

                cycles.emplace_back();
				cycles.back().reserve(s);
                cycles.back().push_back(node);

                for (int to = next[node]; to != node; to = next[to])
                    cycles.back().push_back(to);

                for (int c : cycles.back())
                    cycle_size[c] = s;
            }

        if (need_start) {
            start_max.assign(n, 0);

            for (int i = int(que.size()) - 1; i >= 0; --i) {
                int node = que[i];
                int to = next[node];
                start_max[node] += to == -1 ? 1 : start_max[to];
            }
        }

        if (need_end) {
            end_max.assign(n, 1);

            for (int i = 0; i < int(que.size()); ++i) {
                int node = que[i];
                int to = next[node];

                if (to != -1)
                    end_max[to] = end_max[node] + 1;
            }
        }
    }
};
