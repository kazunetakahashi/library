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
