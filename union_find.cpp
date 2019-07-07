#include <vector>
using namespace std;

class UnionFind
{
public:
  vector<long long> par;

  UnionFind(int n) : par(n, -1) {}
  void init(int n)
  {
    par.assign(n, -1);
  }

  int root(int x)
  {
    if (par[x] < 0)
    {
      return x;
    }
    return par[x] = root(par[x]);
  }

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
};