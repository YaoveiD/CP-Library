/*
*  author: yaoveil
*  date:   2021-06-22 23:16:37
*/

//undigraph or digraph
template<typename T>
vector<vector<T>> floyd(const graph<T>& g) {
  int N = g.n;
  vector<vector<T>> dis(N, vector<T>(N, inf));
  for (int i = 0; i < N; ++i) {
    dis[i][i] = 0;
  }
  for (auto e : g.edges) {
    dis[e.from][e.to] = e.cost;
    //undigraph
    dis[e.to][e.from] = e.cost;
  }
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (dis[i][k] + dis[k][j] < dis[i][j]) {
          dis[i][j] = dis[i][k] + dis[k][j];
        }
      }
    }
  }
  return dis;
}