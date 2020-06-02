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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: Flow/MaxFlow.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f1a76f66cca677c6e628d9ca58a6c8fc">Flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/Flow/MaxFlow.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-02 17:08:46+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Flow/MaxFlow.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

