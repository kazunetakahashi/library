#include <vector>
using namespace std;

class UnionFind
{
  int N;
  vector<int> par;

public:
  UnionFind() : N{0} {}
  UnionFind(int N) : N{N}, par(N, -1) {}

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

  int size(int x)
  {
    return -par[root(x)];
  }

  int count_parts()
  {
    int ans{0};
    for (auto i = 0; i < N; i++)
    {
      if (root(i) < 0)
      {
        ++ans;
      }
    }
    return ans;
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