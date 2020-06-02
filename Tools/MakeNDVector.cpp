#include <vector>
using namespace std;

// ----- 2D, 3D, 4D vectors -----
// Referring to ymatsux-san's source code: https://atcoder.jp/contests/abc138/submissions/7018300

template <typename T>
vector<vector<T>> Make2DVector(size_t d0, size_t d1, T v = T{})
{
  return vector<vector<T>>(d0, vector<T>(d1, v));
}

template <typename T>
vector<vector<vector<T>>> Make3DVector(size_t d0, size_t d1, size_t d2, T v = T{})
{
  return vector<vector<vector<T>>>(d0, Make2DVector(d1, d2, v));
}

template <typename T>
vector<vector<vector<vector<T>>>> Make4DVector(size_t d0, size_t d1, size_t d2, size_t d3, T v = T{})
{
  return vector<vector<vector<vector<T>>>>(d0, Make3DVector(d1, d2, d3, v));
}
