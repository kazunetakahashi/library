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


# :warning: LCA.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/LCA.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-24 16:29:17+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>
using namespace std;
using ll = long long;

// ----- LCA -----

template <typename T = ll>
class LCA
{
  int N, root, L;
  vector<vector<int>> to;
  vector<vector<T>> co;
  vector<int> dep;
  vector<T> costs;
  vector<vector<int>> par;

public:
  LCA(int n) : N{n}, L{0}, to(n), co(n), dep(n), costs(n)
  {
    while ((1 << L) < N)
    {
      ++L;
    }
    par = vector<vector<int>>(N + 1, vector<int>(L, N));
  }

  void add_edge(int a, int b, T c = 0)
  {
    to[a].push_back(b);
    co[a].push_back(c);
    to[b].push_back(a);
    co[b].push_back(c);
  }

  void init(int _root)
  {
    root = _root;
    dfs(root);
    for (auto i = 0; i < L - 1; i++)
    {
      for (auto v = 0; v < N; v++)
      {
        if (par[v][i] != -1)
        {
          par[v][i + 1] = par[par[v][i]][i];
        }
      }
    }
  }

  // LCA
  int operator()(int a, int b)
  {
    if (dep[a] > dep[b])
    {
      swap(a, b);
    }
    int gap = dep[b] - dep[a];
    for (auto i = L - 1; i >= 0; i--)
    {
      int len = 1 << i;
      if (gap >= len)
      {
        gap -= len;
        b = par[b][i];
      }
    }
    if (a == b)
    {
      return a;
    }
    for (auto i = L - 1; i >= 0; i--)
    {
      int na = par[a][i];
      int nb = par[b][i];
      if (na != nb)
      {
        a = na;
        b = nb;
      }
    }
    return par[a][0];
  }

  int length(int a, int b)
  {
    int c = (*this)(a, b);
    return dep[a] + dep[b] - 2 * dep[c];
  }

  T dist(int a, int b)
  {
    int c = (*this)(a, b);
    return costs[a] + costs[b] - 2 * costs[c];
  }

private:
  void dfs(int v, int d = 0, T c = 0, int p = -1)
  {
    if (p != -1)
    {
      par[v][0] = p;
    }
    dep[v] = d;
    costs[v] = c;
    for (auto i = 0u; i < to[v].size(); i++)
    {
      int u = to[v][i];
      if (u == p)
      {
        continue;
      }
      dfs(u, d + 1, c + co[v][i], v);
    }
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "LCA.cpp"
#include <vector>
using namespace std;
using ll = long long;

// ----- LCA -----

template <typename T = ll>
class LCA
{
  int N, root, L;
  vector<vector<int>> to;
  vector<vector<T>> co;
  vector<int> dep;
  vector<T> costs;
  vector<vector<int>> par;

public:
  LCA(int n) : N{n}, L{0}, to(n), co(n), dep(n), costs(n)
  {
    while ((1 << L) < N)
    {
      ++L;
    }
    par = vector<vector<int>>(N + 1, vector<int>(L, N));
  }

  void add_edge(int a, int b, T c = 0)
  {
    to[a].push_back(b);
    co[a].push_back(c);
    to[b].push_back(a);
    co[b].push_back(c);
  }

  void init(int _root)
  {
    root = _root;
    dfs(root);
    for (auto i = 0; i < L - 1; i++)
    {
      for (auto v = 0; v < N; v++)
      {
        if (par[v][i] != -1)
        {
          par[v][i + 1] = par[par[v][i]][i];
        }
      }
    }
  }

  // LCA
  int operator()(int a, int b)
  {
    if (dep[a] > dep[b])
    {
      swap(a, b);
    }
    int gap = dep[b] - dep[a];
    for (auto i = L - 1; i >= 0; i--)
    {
      int len = 1 << i;
      if (gap >= len)
      {
        gap -= len;
        b = par[b][i];
      }
    }
    if (a == b)
    {
      return a;
    }
    for (auto i = L - 1; i >= 0; i--)
    {
      int na = par[a][i];
      int nb = par[b][i];
      if (na != nb)
      {
        a = na;
        b = nb;
      }
    }
    return par[a][0];
  }

  int length(int a, int b)
  {
    int c = (*this)(a, b);
    return dep[a] + dep[b] - 2 * dep[c];
  }

  T dist(int a, int b)
  {
    int c = (*this)(a, b);
    return costs[a] + costs[b] - 2 * costs[c];
  }

private:
  void dfs(int v, int d = 0, T c = 0, int p = -1)
  {
    if (p != -1)
    {
      par[v][0] = p;
    }
    dep[v] = d;
    costs[v] = c;
    for (auto i = 0u; i < to[v].size(); i++)
    {
      int u = to[v][i];
      if (u == p)
      {
        continue;
      }
      dfs(u, d + 1, c + co[v][i], v);
    }
  }
};

```
{% endraw %}

<a href="../index.html">Back to top page</a>

