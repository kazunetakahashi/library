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


# :warning: Graph/ReadGraph.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/ReadGraph.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-18 07:39:57+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// ----- ReadGraph -----
// Referring to ymatsux-san's source code: https://atcoder.jp/contests/abc138/submissions/7016619

struct Edge
{
  int src, dst, id;
  // ll cost;
  Edge() {}
  Edge(int src, int dst, int id) : src{src}, dst{dst}, id{id} {}
  // Edge(int src, int dst, ll cost) : src{src}, dst{dst}, cost{cost} {}

  void added_edge(vector<vector<Edge>> &V)
  {
    V[src].push_back(*this);
  }

  void added_rev(vector<vector<Edge>> &V)
  {
    V[dst].push_back(rev());
  }

  Edge rev()
  {
    Edge edge{*this};
    swap(edge.src, edge.dst);
    return edge;
  }
};

tuple<vector<vector<Edge>>, vector<Edge>> ReadGraphWithEdges(int N, int M, bool is_undirected = true, bool is_one_indexed = true)
{
  vector<vector<Edge>> V(N);
  vector<Edge> E(M);
  for (auto i = 0; i < M; ++i)
  {
    int v, w;
    cin >> v >> w;
    if (is_one_indexed)
    {
      --v;
      --w;
    }
    Edge edge{v, w, i};
    edge.added_edge(V);
    if (is_undirected)
    {
      edge.added_rev(V);
    }
    E.push_back(edge);
  }
  return make_tuple(V, E);
}

vector<vector<Edge>> ReadGraph(int N, int M, bool is_undirected = true, bool is_one_indexed = true)
{
  return get<0>(ReadGraphWithEdges(N, M, is_undirected, is_one_indexed));
}

tuple<vector<vector<Edge>>, vector<Edge>> ReadTreeWithEdges(int N)
{
  return ReadGraphWithEdges(N, N - 1);
}

vector<vector<Edge>> ReadTree(int N)
{
  return ReadGraph(N, N - 1);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/ReadGraph.cpp"
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// ----- ReadGraph -----
// Referring to ymatsux-san's source code: https://atcoder.jp/contests/abc138/submissions/7016619

struct Edge
{
  int src, dst, id;
  // ll cost;
  Edge() {}
  Edge(int src, int dst, int id) : src{src}, dst{dst}, id{id} {}
  // Edge(int src, int dst, ll cost) : src{src}, dst{dst}, cost{cost} {}

  void added_edge(vector<vector<Edge>> &V)
  {
    V[src].push_back(*this);
  }

  void added_rev(vector<vector<Edge>> &V)
  {
    V[dst].push_back(rev());
  }

  Edge rev()
  {
    Edge edge{*this};
    swap(edge.src, edge.dst);
    return edge;
  }
};

tuple<vector<vector<Edge>>, vector<Edge>> ReadGraphWithEdges(int N, int M, bool is_undirected = true, bool is_one_indexed = true)
{
  vector<vector<Edge>> V(N);
  vector<Edge> E(M);
  for (auto i = 0; i < M; ++i)
  {
    int v, w;
    cin >> v >> w;
    if (is_one_indexed)
    {
      --v;
      --w;
    }
    Edge edge{v, w, i};
    edge.added_edge(V);
    if (is_undirected)
    {
      edge.added_rev(V);
    }
    E.push_back(edge);
  }
  return make_tuple(V, E);
}

vector<vector<Edge>> ReadGraph(int N, int M, bool is_undirected = true, bool is_one_indexed = true)
{
  return get<0>(ReadGraphWithEdges(N, M, is_undirected, is_one_indexed));
}

tuple<vector<vector<Edge>>, vector<Edge>> ReadTreeWithEdges(int N)
{
  return ReadGraphWithEdges(N, N - 1);
}

vector<vector<Edge>> ReadTree(int N)
{
  return ReadGraph(N, N - 1);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

