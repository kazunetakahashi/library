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


# :warning: Dinic.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/Dinic.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-03 11:39:20+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Dinic.cpp"
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

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp

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

```
{% endraw %}

<a href="../index.html">Back to top page</a>

