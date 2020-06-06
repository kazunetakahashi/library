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


# :warning: Graph/WarshallFloyd.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/WarshallFloyd.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-07 03:13:06+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using ll = long long;

template <typename T>
void ch_min(T &left, T right)
{
  if (left > right)
  {
    left = right;
  }
}

// ----- WarshallFloyd -----

template <typename T>
void WarshallFloyd(vector<vector<T>> &V, T infinity = numeric_limits<T>::max())
{
  // It is valid to apply this method for
  //  - a directed/undirected graph,
  //  - a graph whose edge may be negative.
  //    - Negative cycle can be detected by V[i][i] < 0 if we initialize V[i][i] = 0.
  auto N{static_cast<int>(V.size())};
  for (auto k{0}; k < N; ++k)
  {
    for (auto i{0}; i < N; ++i)
    {
      for (auto j{0}; j < N; ++j)
      {
        if (V[i][k] == infinity || V[k][j] == infinity)
        {
          continue;
        }
        ch_min(V[i][j], V[i][k] + V[k][j]);
      }
    }
  }
}

// ----- main -----

template <typename T>
constexpr T Infty() { return numeric_limits<T>::max(); }

int main()
{
  int N, M;
  cin >> N >> M;
  vector<vector<ll>> D(N, vector<ll>(N, Infty<ll>()));
  for (auto i{0}; i < M; ++i)
  {
    int A, B;
    ll C;
    cin >> A >> B >> C;
    D[A][B] = C;
  }
  for (auto i{0}; i < N; ++i)
  {
    D[i][i] = 0;
  }
  WarshallFloyd(D);
  for (auto i{0}; i < N; ++i)
  {
    if (D[i][i] < 0)
    {
      cout << "NEGATIVE CYCLE" << endl;
      return 0;
    }
  }
  for (auto i{0}; i < N; ++i)
  {
    for (auto j{0}; j < N; ++j)
    {
      cout << (D[i][j] == Infty<ll>() ? "INF" : to_string(D[i][j]));
      if (j < N - 1)
      {
        cout << " ";
      }
      else
      {
        cout << endl;
      }
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/WarshallFloyd.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using ll = long long;

template <typename T>
void ch_min(T &left, T right)
{
  if (left > right)
  {
    left = right;
  }
}

// ----- WarshallFloyd -----

template <typename T>
void WarshallFloyd(vector<vector<T>> &V, T infinity = numeric_limits<T>::max())
{
  // It is valid to apply this method for
  //  - a directed/undirected graph,
  //  - a graph whose edge may be negative.
  //    - Negative cycle can be detected by V[i][i] < 0 if we initialize V[i][i] = 0.
  auto N{static_cast<int>(V.size())};
  for (auto k{0}; k < N; ++k)
  {
    for (auto i{0}; i < N; ++i)
    {
      for (auto j{0}; j < N; ++j)
      {
        if (V[i][k] == infinity || V[k][j] == infinity)
        {
          continue;
        }
        ch_min(V[i][j], V[i][k] + V[k][j]);
      }
    }
  }
}

// ----- main -----

template <typename T>
constexpr T Infty() { return numeric_limits<T>::max(); }

int main()
{
  int N, M;
  cin >> N >> M;
  vector<vector<ll>> D(N, vector<ll>(N, Infty<ll>()));
  for (auto i{0}; i < M; ++i)
  {
    int A, B;
    ll C;
    cin >> A >> B >> C;
    D[A][B] = C;
  }
  for (auto i{0}; i < N; ++i)
  {
    D[i][i] = 0;
  }
  WarshallFloyd(D);
  for (auto i{0}; i < N; ++i)
  {
    if (D[i][i] < 0)
    {
      cout << "NEGATIVE CYCLE" << endl;
      return 0;
    }
  }
  for (auto i{0}; i < N; ++i)
  {
    for (auto j{0}; j < N; ++j)
    {
      cout << (D[i][j] == Infty<ll>() ? "INF" : to_string(D[i][j]));
      if (j < N - 1)
      {
        cout << " ";
      }
      else
      {
        cout << endl;
      }
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

