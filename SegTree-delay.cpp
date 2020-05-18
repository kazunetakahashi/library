#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

using ll = long long;

// ----- SegTree -----
// This source code can be compiled only by C++17 or upper version. C++14 or lower is not allowed.
// Referring to https://beet-aizu.github.io/library/library/segtree/basic/chien.cpp.html

template <typename T, typename U>
class SegTree
{
  int N, height;
  T(*update_T)
  (T, T);
  T(*merge)
  (T, U);
  U(*update_U)
  (U, U);
  T unit_T;
  U unit_U;
  vector<T> data;
  vector<U> delay;

public:
  SegTree(int n, T (*update_T)(T, T), T (*merge)(T, U), U (*update_U)(U, U), T unit_T, U unit_U, T init_T) : N{1}, height{0}, update_T{update_T}, merge{merge}, update_U{update_U}, unit_T{unit_T}, unit_U{unit_U}
  {
    while (N < n)
    {
      N <<= 1;
      ++height;
    }
    data.assign(2 * N, unit_T);
    delay.assign(2 * N, unit_U);
    for (int i = 0; i < N; i++)
    {
      data[n + i] = init_T;
    }
    for (int i = N - 1; i; i--)
    {
      data[i] = update_T(data[(i << 1) | 0], data[(i << 1) | 1]);
    }
  }

  SegTree(int n, T (*update_T)(T, T), T (*merge)(T, U), U (*update_U)(U, U), T unit_T, U unit_U) : SegTree(n, update_T, merge, update_U, unit_T, unit_U, unit_T) {}

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
        delay[l] = update_U(delay[l], x);
        ++l;
      }
      if (r & 1)
      {
        --r;
        delay[r] = update_U(delay[r], x);
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
        vl = update_T(vl, append(l++));
      }
      if (r & 1)
      {
        vr = update_T(append(--r), vr);
      }
    }
    return update_T(vl, vr);
  }

private:
  inline T append(int k)
  {
    return delay[k] == unit_U ? data[k] : merge(data[k], delay[k]);
  }

  inline void propagate(int k)
  {
    if (delay[k] == unit_U)
    {
      return;
    }
    delay[(k << 1) | 0] = update_U(delay[(k << 1) | 0], delay[k]);
    delay[(k << 1) | 1] = update_U(delay[(k << 1) | 1], delay[k]);
    data[k] = append(k);
    delay[k] = unit_U;
  }

  inline void propagate_down(int k)
  {
    for (auto i = height; i; i--)
    {
      propagate(k >> i);
    }
  }

  inline void recalc(int k)
  {
    while (k >>= 1)
    {
      data[k] = update_T(append((k << 1) | 0), append((k << 1) | 1));
    }
  }
};

class RMQ_RUQ : public SegTree<ll, ll>
{
  /*
  constexpr static auto update_T{[](auto a, auto b) { return min(a, b); }};
  constexpr static auto update_U{[](auto a, auto b) { return b; }};
  */
  constexpr static ll INFTY{2147483647LL};

public:
  /*
  RMQ_RUQ(int N) : SegTree<ll, ll>{N, update_T, update_U, update_U, INFTY, INFTY} {};
  */
  RMQ_RUQ(int N) : SegTree<ll, ll>{N, [](auto a, auto b) { return min(a, b); }, [](auto a, auto b) { return b; }, [](auto a, auto b) { return b; }, INFTY, INFTY} {};
};

class RMQ_RAQ : public SegTree<ll, ll>
{
  /*
  constexpr static auto update_T{[](auto a, auto b) { return min(a, b); }};
  constexpr static auto update_U{[](auto a, auto b) { return a + b; }};
  */
  constexpr static ll INFTY{2147483647LL};

public:
  /*
  RMQ_RAQ(int N) : SegTree<ll, ll>{N, update_T, update_U, update_U, INFTY, 0} {};
  */
  RMQ_RAQ(int N) : SegTree<ll, ll>{N, [](auto a, auto b) { return min(a, b); }, [](auto a, auto b) { return a + b; }, [](auto a, auto b) { return a + b; }, INFTY, 0} {};
};

class RSQ_RAQ : public SegTree<tuple<ll, ll>, ll>
{
  using Pair = tuple<ll, ll>;
  constexpr static auto update_T{[](Pair a, Pair b) { return Pair(get<0>(a) + get<0>(b), get<1>(a) + get<1>(b)); }};
  constexpr static auto merge{[](Pair a, auto b) { return Pair(get<0>(a) + b * get<1>(a), get<1>(a)); }};
  constexpr static auto update_U{[](auto a, auto b) { return a + b; }};

public:
  RSQ_RAQ(int N) : SegTree<tuple<ll, ll>, ll>{N, update_T, merge, update_U, Pair(0, 0), 0, Pair(0, 1)} {};

  ll query(int a, int b) { return get<0>(SegTree<tuple<ll, ll>, ll>::query(a, b)); }
};

class RSQ_RUQ : public SegTree<tuple<ll, ll>, ll>
{
  using Pair = tuple<ll, ll>;
  constexpr static auto update_T{[](Pair a, Pair b) { return Pair(get<0>(a) + get<0>(b), get<1>(a) + get<1>(b)); }};
  constexpr static auto merge{[](Pair a, auto b) { return Pair(get<0>(a) + b * get<1>(a), get<1>(a)); }};
  constexpr static auto update_U{[](auto a, auto b) { return b; }};
  constexpr static ll INFTY{2147483647LL};

public:
  RSQ_RUQ(int N) : SegTree<tuple<ll, ll>, ll>{N, update_T, merge, update_U, Pair(0, 0), -INFTY, Pair(0, 1)} {};

  ll query(int a, int b) { return get<0>(SegTree<tuple<ll, ll>, ll>::query(a, b)); }
};

class RMQ : public RMQ_RUQ
{
public:
  RMQ(int N) : RMQ_RUQ(N){};
  void update(int a, ll x) { RMQ_RUQ::update(a, a + 1, x); }
};

class RUQ : public RMQ_RUQ
{
public:
  RUQ(int N) : RMQ_RUQ(N){};
  ll query(int a) { return RMQ_RUQ::query(a, a + 1); }
};

class RSQ : public RSQ_RAQ
{
public:
  RSQ(int N) : RSQ_RAQ(N){};
  void update(int a, ll x) { RSQ_RAQ::update(a, a + 1, x); }
};

class RAQ : public RSQ_RAQ
{
public:
  RAQ(int N) : RSQ_RAQ(N){};
  ll query(int a) { return RSQ_RAQ::query(a, a + 1); }
};

int main()
{
  int N, Q;
  cin >> N >> Q;
  RSQ_RAQ tree{N};
  for (auto i = 0; i < Q; i++)
  {
    int c;
    cin >> c;
    if (c == 0)
    {
      int s, t;
      ll x;
      cin >> s >> t >> x;
      --s;
      --t;
      tree.update(s, t + 1, x);
    }
    if (c == 1)
    {
      int s, t;
      cin >> s >> t;  
      --s;
      --t;
      cout << tree.query(s, t + 1) << endl;
    }
  }
}
