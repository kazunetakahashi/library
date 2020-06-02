#include <vector>
using namespace std;
using ll = long long;

// ----- LCA -----

class LCA
{
  // helper classes
  struct Edge
  {
    // Initialized by initializer list. Take care for the order of the field.
    int src, dst;
    ll cost;
  };

  struct Vertex
  {
    int depth;
    ll length;
  };

  // fields
  int N, root, L;
  vector<vector<Edge>> E;
  vector<Vertex> V;
  vector<vector<int>> ancestors;

  // methods
public:
  LCA(int N, int root = 0);
  void add_edge(int a, int b, ll c = 0);
  void init();
  void init(int root); // after adding all edges.

  // LCA
  int operator()(int a, int b);

  int depth(int a, int b) { return V[a].depth + V[b].depth - 2 * V[(*this)(a, b)].depth; }
  int depth(int v) { return depth(v, root); }
  ll length(int a, int b) { return V[a].length + V[b].length - 2 * V[(*this)(a, b)].length; }
  ll length(int v) { return length(v, root); }
  int parent(int v) { return ancestors[v][0]; }

private:
  void dfs(int v, int d = 0, ll l = 0, int p = -1);
};

// LCA: implement

LCA::LCA(int N, int root) : N{N}, root{root}, L{0}, E(N), V(N)
{
  while ((1 << L) < N)
  {
    ++L;
  }
  ancestors = vector<vector<int>>(N + 1, vector<int>(L, N));
}

void LCA::add_edge(int a, int b, ll c)
{
  E[a].push_back(LCA::Edge{a, b, c});
  E[b].push_back(LCA::Edge{b, a, c});
}

void LCA::init(int root)
{
  LCA::root = root;
  init();
}

void LCA::init()
{
  dfs(root);
  for (auto i = 0; i < L - 1; i++)
  {
    for (auto v = 0; v < N; v++)
    {
      if (ancestors[v][i] != -1)
      {
        ancestors[v][i + 1] = ancestors[ancestors[v][i]][i];
      }
    }
  }
}

int LCA::operator()(int a, int b)
{
  if (V[a].depth > V[b].depth)
  {
    swap(a, b);
  }
  int gap = V[b].depth - V[a].depth;
  for (auto i = L - 1; i >= 0; i--)
  {
    int len{1 << i};
    if (gap >= len)
    {
      gap -= len;
      b = ancestors[b][i];
    }
  }
  if (a == b)
  {
    return a;
  }
  for (auto i = L - 1; i >= 0; i--)
  {
    int na{ancestors[a][i]};
    int nb{ancestors[b][i]};
    if (na != nb)
    {
      a = na;
      b = nb;
    }
  }
  return ancestors[a][0];
}

void LCA::dfs(int v, int d, ll l, int p)
{
  if (p != -1)
  {
    ancestors[v][0] = p;
  }
  V[v].depth = d;
  V[v].length = l;
  for (auto const &e : E[v])
  {
    int u{e.dst};
    if (u == p)
    {
      continue;
    }
    dfs(u, d + 1, l + e.cost, v);
  }
}
