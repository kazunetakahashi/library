#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

// ----- SegTree -----

template <typename T, typename U>
class SegTree
{
  int N, height;
  T(*f)
  (T, T);
  T(*g)
  (T, U);
  U(*h)
  (U, U);
  T unit_T;
  U unit_U;
  vector<T> data;
  vector<U> delay;

public:
  SegTree(int n, T (*f)(T, T), T (*g)(T, U), U (*h)(U, U), T unit_T, U unit_U) : N{1}, height{0}, f{f}, g{g}, h{h}, unit_T{unit_T}, unit_U{unit_U}
  {
    while (N < n)
    {
      N <<= 1;
      ++height;
    }
    data.assign(2 * N - 1, unit_T);
    delay.assign(2 * N - 1, unit_U);
  }

  void update(int a, int b, U x)
  {
    if (a >= b)
    {
      return;
    }
    propagate_down(a += N);
    propagate_down(b += N - 1);
    for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
      {
        delay[l] = h(delay[l], x);
        ++l;
      }
      if (r & 1)
      {
        --r;
        delay[r] = h(delay[r], x);
      }
    }
    recalc(a);
    recalc(b);
  }

  T query(int a, int b)
  {
    if (a >= b)
    {
      return unit_T;
    }
    propagate_down(a += N);
    propagate_down(b += N - 1);
    T vl{unit_T}, vr{unit_T};
    for (auto l = a, r = b + 1; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
      {
        vl = f(vl, append(l++));
      }
      if (r & 1)
      {
        vr = f(append(--r), vr);
      }
    }
    return f(vl, vr);
  }

private:
  inline T append(int k)
  {
    return delay[k] == unit_U ? data[k] : g(data[k], delay[k]);
  }

  inline void propagate(int k)
  {
    if (delay[k] == unit_U)
    {
      return;
    }
    delay[(k << 1) | 0] = h(delay[(k << 1) | 0], delay[k]);
    delay[(k << 1) | 1] = h(delay[(k << 1) | 1], delay[k]);
    data[k] = append(k);
    delay[k] = unit_U;
  }

  inline void propagate_down(int k)
  {
    for (auto i = height; i >= 0; i--)
    {
      propagate(k >> i);
    }
  }

  inline void recalc(int k)
  {
    while (k >>= 1)
    {
      data[k] = f(append((k << 1) | 0), append((k << 1) | 1));
    }
  }

};
