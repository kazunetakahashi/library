#include "../Dinic.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp"

int main()
{
  int N, M;
  cin >> N >> M;
  Dinic dinic{N};
  for (auto i = 0; i < M; i++)
  {
    int from, to;
    ll cap;
    cin >> from >> to >> cap;
    dinic.add_edge(from, to, cap);
  }
  cout << dinic.max_flow(0, N - 1) << endl;
}
