#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;

// ----- Dinic -----

class Dinic
{
  struct edge
  {
    int to;
    ll cap;
    int rev;
  };
  constexpr static ll INFTY = 10000000000000010LL;

  int N;
  vector<vector<edge>> G;
  vector<ll> level;
  vector<size_t> iter;

public:
  Dinic() {}
  Dinic(int N) : N{N}, G(N), level(N), iter(N) {}

  void add_edge(int from, int to, ll cap = 1LL)
  {
    G[from].push_back({to, cap, static_cast<int>(G[to].size())});
    G[to].push_back({from, 0, static_cast<int>(G[from].size() - 1)});
  }

  ll max_flow(int s, int t)
  {
    ll flow{0LL};
    while (true)
    {
      bfs(s);
      if (level[t] < 0)
      {
        return flow;
      }
      fill(iter.begin(), iter.end(), 0u);
      ll f;
      while ((f = dfs(s, t, INFTY)) > 0LL)
      {
        flow += f;
      }
    }
  }

private:
  void bfs(int s)
  {
    fill(level.begin(), level.end(), -1);
    queue<int> Q;
    level[s] = 0;
    Q.push(s);
    while (!Q.empty())
    {
      int v{Q.front()};
      Q.pop();
      for (auto &e : G[v])
      {
        if (e.cap > 0LL && level[e.to] < 0)
        {
          level[e.to] = level[v] + 1;
          Q.push(e.to);
        }
      }
    }
  }

  ll dfs(int v, int t, ll f)
  {
    if (v == t)
    {
      return f;
    }
    for (auto &i = iter[v]; i < G[v].size(); i++)
    {
      edge &e{G[v][i]};
      if (e.cap > 0LL && level[v] < level[e.to])
      {
        ll d{dfs(e.to, t, min(f, e.cap))};
        if (d > 0LL)
        {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0LL;
  }
};
