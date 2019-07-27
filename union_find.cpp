#include <vector>
using namespace std;

class UnionFind
{
  vector<long long> par;

public:
  UnionFind() {}
  UnionFind(int n) : par(n, -1) {}

  bool is_same(int x, int y)
  {
    return root(x) == root(y);
  }

  bool merge(int x, int y)
  {
    x = root(x);
    y = root(y);
    if (x == y)
    {
      return false;
    }
    if (par[x] > par[y])
    {
      swap(x, y);
    }
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  long long size(int x)
  {
    return -par[root(x)];
  }

private:
  int root(int x)
  {
    if (par[x] < 0)
    {
      return x;
    }
    return par[x] = root(par[x]);
  }
};