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
