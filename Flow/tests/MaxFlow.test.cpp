#include "../MaxFlow.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp"

int main()
{
  int N, M;
  cin >> N >> M;
  MaxFlow flow{N};
  for (auto i = 0; i < M; i++)
  {
    int from, to;
    ll cap;
    cin >> from >> to >> cap;
    flow.add_edge(from, to, cap);
  }
  cout << flow.max_flow(0, N - 1) << endl;
}
