/*
*  author: yaoveil
*  date:   2021-06-22 23:15:32
*/
template<typename T>
class Spfa {
public:
  int N;
  vector<ll> dis;
  vector<ll> times;

  Spfa(int _N) {
    N = _N;
    dis.assign(N, inf);
    times.assign(N, 0);
  }

  //a simple graph
  void spfa(vector<vector<pair<int, T>>>& edge, int source = 0) {
    queue<int> q;
    vector<bool> vis(N, false);
    dis[source] = 0;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = false;
      for (auto e : edge[u]) {
        int v = e.first;
        if (dis[v] > dis[u] + e.second) {
          dis[v] = dis[u] + e.second;
          if (!vis[v] && times[v] < N) {
            times[v]++;
            q.push(v);
            vis[v] = true;
          }
        }
      }
    }
  }

  void spfa(const graph<T>& g, int source = 0) {
    queue<int> q;
    vector<bool> vis(N, false);
    dis[source] = 0;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = false;
      for (int id : g.g[u]) {
        auto e = g.edges[id];
        int v = e.from ^ e.to ^ u;
        if (dis[v] > dis[u] + e.cost) {
          dis[v] = dis[u] + e.cost;
          if (!vis[v] && times[v] < N) {
            times[v]++;
            q.push(v);
            vis[v] = true;
          }
        }
      }
    }
  }
};

template<typename T>
bool BF(const graph<T>& g, vector<T>& dist, int src = 0) {
  int N = g.n;
  dist[src] = 0;
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j < (int) g.edges.size(); ++j) {
      int from = g.edges[j].from;
      int to = g.edges[j].to;
      int cost = g.edges[j].cost;
      if (dist[to] > dist[from] + cost) {
        dist[to] = dist[from] + cost;
        if (i == N) {
          return false;
        }
      }
    }
  }
  return true;
}
