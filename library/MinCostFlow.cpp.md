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


# :warning: MinCostFlow.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/MinCostFlow.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-24 16:29:17+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define DEBUG 1

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

using ll = long long;

// ----- MinCostFlow -----

using Info = tuple<ll, int>;

struct Edge
{
  int to;
  ll cap, cost;
  int rev;
};

class MinCostFlow
{
  int N;
  vector<vector<Edge>> G;
  vector<ll> h, dist;
  vector<int> prev_v, prev_e;
  constexpr static ll INFTY = 10000000000000010LL;

public:
  MinCostFlow() {}

  MinCostFlow(int n) : N(n)
  {
    G.resize(N);
    h.resize(N);
    dist.resize(N);
    prev_v.resize(N);
    prev_e.resize(N);
  }

  void add_edge(int from, int to, ll cap, ll cost)
  {
    G[from].emplace_back(to, cap, cost, static_cast<int>(G[to].size()));
    G[to].emplace_back(from, 0, -cost, static_cast<int>(G[from].size() - 1));
  }

  ll min_cost_flow(int s, int t, ll f)
  {
    ll res = 0;
    fill(h.begin(), h.end(), 0);
    while (f > 0)
    {
      priority_queue<Info, vector<Info>, greater<Info>> Q;
      fill(dist.begin(), dist.end(), INFTY);
      dist[s] = 0;
      Q.push(Info(0, s));
      while (!Q.empty())
      {
        Info p = Q.top();
        Q.pop();
        int v = get<1>(p);
        if (dist[v] < get<0>(p))
        {
          continue;
        }
        for (auto i = 0; i < (int)G[v].size(); i++)
        {
          Edge &e = G[v][i];
          ll tmp = dist[v] + e.cost + h[v] - h[e.to];
          if (e.cap > 0 && dist[e.to] > tmp)
          {
            dist[e.to] = tmp;
            prev_v[e.to] = v;
            prev_e[e.to] = i;
            Q.push(Info(dist[e.to], e.to));
          }
        }
      }
      if (dist[t] == INFTY)
      {
        return -1;
      }
      for (auto v = 0; v < N; v++)
      {
        h[v] += dist[v];
      }
      ll d = f;
      for (auto v = t; v != s; v = prev_v[v])
      {
        d = min(d, G[prev_v[v]][prev_e[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for (auto v = t; v != s; v = prev_v[v])
      {
        Edge &e = G[prev_v[v]][prev_e[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};

// ------------------------------------------------------------

int N, M;
ll F;
MinCostFlow flow;

int main()
{
  cin >> N >> M >> F;
  flow = MinCostFlow(N);
  for (auto i = 0; i < M; i++)
  {
    int u, v;
    ll c, d;
    cin >> u >> v >> c >> d;
    flow.add_edge(u, v, c, d);
  }
  cout << flow.min_cost_flow(0, N - 1, F) << endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "MinCostFlow.cpp"
#define DEBUG 1

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

using ll = long long;

// ----- MinCostFlow -----

using Info = tuple<ll, int>;

struct Edge
{
  int to;
  ll cap, cost;
  int rev;
};

class MinCostFlow
{
  int N;
  vector<vector<Edge>> G;
  vector<ll> h, dist;
  vector<int> prev_v, prev_e;
  constexpr static ll INFTY = 10000000000000010LL;

public:
  MinCostFlow() {}

  MinCostFlow(int n) : N(n)
  {
    G.resize(N);
    h.resize(N);
    dist.resize(N);
    prev_v.resize(N);
    prev_e.resize(N);
  }

  void add_edge(int from, int to, ll cap, ll cost)
  {
    G[from].emplace_back(to, cap, cost, static_cast<int>(G[to].size()));
    G[to].emplace_back(from, 0, -cost, static_cast<int>(G[from].size() - 1));
  }

  ll min_cost_flow(int s, int t, ll f)
  {
    ll res = 0;
    fill(h.begin(), h.end(), 0);
    while (f > 0)
    {
      priority_queue<Info, vector<Info>, greater<Info>> Q;
      fill(dist.begin(), dist.end(), INFTY);
      dist[s] = 0;
      Q.push(Info(0, s));
      while (!Q.empty())
      {
        Info p = Q.top();
        Q.pop();
        int v = get<1>(p);
        if (dist[v] < get<0>(p))
        {
          continue;
        }
        for (auto i = 0; i < (int)G[v].size(); i++)
        {
          Edge &e = G[v][i];
          ll tmp = dist[v] + e.cost + h[v] - h[e.to];
          if (e.cap > 0 && dist[e.to] > tmp)
          {
            dist[e.to] = tmp;
            prev_v[e.to] = v;
            prev_e[e.to] = i;
            Q.push(Info(dist[e.to], e.to));
          }
        }
      }
      if (dist[t] == INFTY)
      {
        return -1;
      }
      for (auto v = 0; v < N; v++)
      {
        h[v] += dist[v];
      }
      ll d = f;
      for (auto v = t; v != s; v = prev_v[v])
      {
        d = min(d, G[prev_v[v]][prev_e[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for (auto v = t; v != s; v = prev_v[v])
      {
        Edge &e = G[prev_v[v]][prev_e[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};

// ------------------------------------------------------------

int N, M;
ll F;
MinCostFlow flow;

int main()
{
  cin >> N >> M >> F;
  flow = MinCostFlow(N);
  for (auto i = 0; i < M; i++)
  {
    int u, v;
    ll c, d;
    cin >> u >> v >> c >> d;
    flow.add_edge(u, v, c, d);
  }
  cout << flow.min_cost_flow(0, N - 1, F) << endl;
}

```
{% endraw %}

<a href="../index.html">Back to top page</a>

