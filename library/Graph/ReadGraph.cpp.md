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
    - Last commit date: 2020-07-02 07:52:27+09:00




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
  int src, dst, id, rev;
  // ll cost;
  Edge() {}
  Edge(int src, int dst, int id, int rev) : src{src}, dst{dst}, id{id}, rev{rev} {}

  void added_edge(vector<vector<Edge>> &V)
  {
    V[src].push_back(*this);
  }

  void added_rev(vector<vector<Edge>> &V)
  {
    V[dst].push_back(rev_edge());
  }

  Edge rev_edge()
  {
    Edge edge{*this};
    swap(edge.src, edge.dst);
    swap(edge.id, edge.rev);
    return edge;
  }
};

enum class GraphType
{
  Undirected,
  Directed,
  RevEdge,
};

tuple<vector<vector<Edge>>, vector<Edge>> ReadGraphWithEdges(int N, int M, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  vector<vector<Edge>> V(N);
  vector<Edge> E;
  for (auto i = 0; i < M; ++i)
  {
    int v, w;
    cin >> v >> w;
    if (is_one_indexed)
    {
      --v;
      --w;
    }
    switch (type)
    {
    case GraphType::Undirected:
    {
      Edge edge{v, w, static_cast<int>(E.size()), static_cast<int>(E.size())};
      edge.added_edge(V);
      edge.added_rev(V);
      E.push_back(edge);
      break;
    }
    case GraphType::Directed:
    {
      Edge edge{v, w, static_cast<int>(E.size()), static_cast<int>(E.size())};
      edge.added_edge(V);
      E.push_back(edge);
      break;
    }
    case GraphType::RevEdge:
    {
      Edge edge{v, w, static_cast<int>(E.size()), static_cast<int>(E.size()) + 1};
      edge.added_edge(V);
      edge.added_rev(V);
      E.push_back(edge);
      E.push_back(edge.rev_edge());
      break;
    }
    default:
      break;
    }
  }
  return make_tuple(V, E);
}

vector<vector<Edge>> ReadGraph(int N, int M, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  return get<0>(ReadGraphWithEdges(N, M, type, is_one_indexed));
}

tuple<vector<vector<Edge>>, vector<Edge>> ReadTreeWithEdges(int N, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  return ReadGraphWithEdges(N, N - 1, type, is_one_indexed);
}

vector<vector<Edge>> ReadTree(int N, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  return ReadGraph(N, N - 1, type, is_one_indexed);
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
  int src, dst, id, rev;
  // ll cost;
  Edge() {}
  Edge(int src, int dst, int id, int rev) : src{src}, dst{dst}, id{id}, rev{rev} {}

  void added_edge(vector<vector<Edge>> &V)
  {
    V[src].push_back(*this);
  }

  void added_rev(vector<vector<Edge>> &V)
  {
    V[dst].push_back(rev_edge());
  }

  Edge rev_edge()
  {
    Edge edge{*this};
    swap(edge.src, edge.dst);
    swap(edge.id, edge.rev);
    return edge;
  }
};

enum class GraphType
{
  Undirected,
  Directed,
  RevEdge,
};

tuple<vector<vector<Edge>>, vector<Edge>> ReadGraphWithEdges(int N, int M, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  vector<vector<Edge>> V(N);
  vector<Edge> E;
  for (auto i = 0; i < M; ++i)
  {
    int v, w;
    cin >> v >> w;
    if (is_one_indexed)
    {
      --v;
      --w;
    }
    switch (type)
    {
    case GraphType::Undirected:
    {
      Edge edge{v, w, static_cast<int>(E.size()), static_cast<int>(E.size())};
      edge.added_edge(V);
      edge.added_rev(V);
      E.push_back(edge);
      break;
    }
    case GraphType::Directed:
    {
      Edge edge{v, w, static_cast<int>(E.size()), static_cast<int>(E.size())};
      edge.added_edge(V);
      E.push_back(edge);
      break;
    }
    case GraphType::RevEdge:
    {
      Edge edge{v, w, static_cast<int>(E.size()), static_cast<int>(E.size()) + 1};
      edge.added_edge(V);
      edge.added_rev(V);
      E.push_back(edge);
      E.push_back(edge.rev_edge());
      break;
    }
    default:
      break;
    }
  }
  return make_tuple(V, E);
}

vector<vector<Edge>> ReadGraph(int N, int M, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  return get<0>(ReadGraphWithEdges(N, M, type, is_one_indexed));
}

tuple<vector<vector<Edge>>, vector<Edge>> ReadTreeWithEdges(int N, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  return ReadGraphWithEdges(N, N - 1, type, is_one_indexed);
}

vector<vector<Edge>> ReadTree(int N, GraphType type = GraphType::Undirected, bool is_one_indexed = true)
{
  return ReadGraph(N, N - 1, type, is_one_indexed);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

