#include <vector>
using namespace std;

// ----- Bipartite -----

// for C++14
// Bipartite<> graph(N);

template <typename T = int>
class Bipartite
{
public:
  struct edge
  {
    bool used;
    size_t rev;
    int from, to;
    T id;

    edge(int from, int to, size_t rev, T id = T{}, bool used = false) : used{used}, rev{rev}, from{from}, to{to}, id{id} {}
  };

private:
  int N;
  vector<vector<edge>> G;
  vector<edge *> match;
  vector<bool> used;

public:
  Bipartite(int N) : N{N}, G(N), match(N), used(N) {}

  void add_edge(int u, int v, T id = T{})
  {
    G[u].push_back({u, v, G[v].size(), id, false});
    G[v].push_back({v, u, G[u].size() - 1, id, false});
  }

  int bipartite_matching()
  {
    int res{0};
    fill(match.begin(), match.end(), nullptr);
    for (auto v = 0; v < N; v++)
    {
      if (!match[v])
      {
        fill(used.begin(), used.end(), false);
        if (dfs(v))
        {
          ++res;
        }
      }
    }
    for (auto &e : match)
    {
      if (e)
      {
        e->used = true;
      }
    }
    return res;
  }

  vector<edge *> const &matching() const
  {
    return match;
  }

private:
  bool dfs(int v)
  {
    used[v] = true;
    for (auto &e : G[v])
    {
      if (e.used)
      {
        continue;
      }
      auto u{e.to};
      // for C++14
      auto w{match[u]};
      if (!w || (!used[w->to] && dfs(w->to)))
      {
        match[v] = &e;
        match[u] = &G[u][e.rev];
        return true;
      }
    }
    return false;
  }
};
