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
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: LazySegTree.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/LazySegTree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-28 18:24:37+09:00




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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "LazySegTree.cpp"
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

```
{% endraw %}

<a href="../index.html">Back to top page</a>

