---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: Bipartite.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/Bipartite.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-25 19:00:12+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Bipartite.cpp"
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

```
{% endraw %}

<a href="../index.html">Back to top page</a>

