#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// ----- MaxFlow -----

class MaxFlow
{
  struct Edge
  {
    int to;
    ll cap;
    int rev;
  };
  constexpr static ll INFTY = 10000000000000010LL;

  int N;
  vector<vector<Edge>> G;
  vector<bool> used;

public:
  MaxFlow() {}
  MaxFlow(int N) : N{N}
  {
    G.resize(N);
    used.resize(N);
  }

  void add_edge(int from, int to, ll cap = 1LL)
  {
    G[from].push_back({to, cap, static_cast<int>(G[to].size())});
    G[to].push_back({from, 0, static_cast<int>(G[from].size() - 1)});
  }

  ll max_flow(int s, int t)
  {
    ll flow = 0;
    while (true)
    {
      fill(used.begin(), used.end(), false);
      ll f = dfs(s, t, INFTY);
      if (f == 0)
      {
        return flow;
      }
      flow += f;
    }
  }

private:
  ll dfs(int v, int t, ll f)
  {
    if (v == t)
    {
      return f;
    }
    used[v] = true;
    for (auto &e : G[v])
    {
      if (!used[e.to] && e.cap > 0)
      {
        ll d = dfs(e.to, t, min(f, e.cap));
        if (d > 0)
        {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }
};

//---------------------------------------------------

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp

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
