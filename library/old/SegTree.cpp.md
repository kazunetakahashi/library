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


# :warning: old/SegTree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#149603e6c03516362a8da23f624db945">old</a>
* <a href="{{ site.github.repository_url }}/blob/master/old/SegTree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-09 20:11:41+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

// ----- SegTree -----

template <typename T>
class SegTree
{ // 0-indexed, [0, N).
private:
  int N;
  vector<T> dat;
  T unit;  // モノイドの単位元
  T(*func) // モノイドの演算
  (T, T);
  T(*_update) // update で値をどうするか書く
  (T, T);

public:
  SegTree() {}

  SegTree(int n, T unit, T (*func)(T, T), T (*_update)(T, T)) : N{1}, unit{unit}, func{func}, _update{_update}
  {
    while (N < n)
    {
      N *= 2;
    }
    dat = vector<T>(2 * N - 1, unit);
  }

  void update(int k, T a)
  {
    k += N - 1;
    dat[k] = _update(dat[k], a);
    while (k > 0)
    {
      k = (k - 1) / 2;
      dat[k] = func(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

private:
  T find(int a, int b, int k, int l, int r)
  {
    if (r <= a || b <= l)
    {
      return unit;
    }
    if (a <= l && r <= b)
    {
      return dat[k];
    }
    T vl = find(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = find(a, b, k * 2 + 2, (l + r) / 2, r);
    return func(vl, vr);
  }

public:
  T find(int a, int b)
  { // [a, b) の find をする。
    return find(a, b, 0, 0, N);
  }
};

// ----- frequently used examples -----

int N{100010};

// for min
auto func = [](auto x, auto y) {
  return min(x, y);
};
auto _update = [](auto x, auto y) {
  return min(x, y);
};
constexpr ll unit{1LL << 60};
SegTree<ll> tree{N, unit, func, _update};

// for +
auto func2 = [](auto x, auto y) {
  return x + y;
};
auto _update2 = [](auto x, auto y) {
  return y;
};
constexpr ll unit2{0LL};
SegTree<ll> tree2{N, unit2, func2, _update2};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "old/SegTree.cpp"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

// ----- SegTree -----

template <typename T>
class SegTree
{ // 0-indexed, [0, N).
private:
  int N;
  vector<T> dat;
  T unit;  // モノイドの単位元
  T(*func) // モノイドの演算
  (T, T);
  T(*_update) // update で値をどうするか書く
  (T, T);

public:
  SegTree() {}

  SegTree(int n, T unit, T (*func)(T, T), T (*_update)(T, T)) : N{1}, unit{unit}, func{func}, _update{_update}
  {
    while (N < n)
    {
      N *= 2;
    }
    dat = vector<T>(2 * N - 1, unit);
  }

  void update(int k, T a)
  {
    k += N - 1;
    dat[k] = _update(dat[k], a);
    while (k > 0)
    {
      k = (k - 1) / 2;
      dat[k] = func(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

private:
  T find(int a, int b, int k, int l, int r)
  {
    if (r <= a || b <= l)
    {
      return unit;
    }
    if (a <= l && r <= b)
    {
      return dat[k];
    }
    T vl = find(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = find(a, b, k * 2 + 2, (l + r) / 2, r);
    return func(vl, vr);
  }

public:
  T find(int a, int b)
  { // [a, b) の find をする。
    return find(a, b, 0, 0, N);
  }
};

// ----- frequently used examples -----

int N{100010};

// for min
auto func = [](auto x, auto y) {
  return min(x, y);
};
auto _update = [](auto x, auto y) {
  return min(x, y);
};
constexpr ll unit{1LL << 60};
SegTree<ll> tree{N, unit, func, _update};

// for +
auto func2 = [](auto x, auto y) {
  return x + y;
};
auto _update2 = [](auto x, auto y) {
  return y;
};
constexpr ll unit2{0LL};
SegTree<ll> tree2{N, unit2, func2, _update2};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

