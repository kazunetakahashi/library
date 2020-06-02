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


# :warning: Numbers/LinearMod.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#cbebfa21dbe8e87e788d94a76f073807">Numbers</a>
* <a href="{{ site.github.repository_url }}/blob/master/Numbers/LinearMod.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-02 17:08:46+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>
#include <tuple>
#include <cassert>
using namespace std;
using ll = long long;

// for C++14
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }

// ----- LinearMod -----

class LinearMod
{
  vector<ll> A, B, M;

public:
  LinearMod() {}

  void add(ll a, ll b, ll m)
  {
    A.push_back(a);
    B.push_back(b);
    M.push_back(m);
  }

  tuple<ll, ll> get()
  {
    assert(A.size() == B.size() && B.size() == M.size());
    ll x{0}, m{1};
    for (auto i = 0; i < A.size(); i++)
    {
      ll a{A[i] * m};
      ll b{B[i] - A[i] * x};
      ll d{gcd(M[i], a)};
      if (b % d != 0)
      {
        return make_tuple(0, -1);
      }
      ll t{b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d)};
      x = x + m * t;
      m *= M[i] / d;
    }
    return make_tuple(x % m, m);
  }

private:
  static ll extra_gcd(ll a, ll b, ll &x, ll &y)
  {
    ll d{a};
    if (b != 0)
    {
      d = extra_gcd(b, a % b, y, x);
      y -= (a / b) * x;
    }
    else
    {
      x = 1;
      y = 0;
    }
    return d;
  }

  static ll mod_inverse(ll a, ll m)
  {
    ll x, y;
    extra_gcd(a, m, x, y);
    return (m + x % m) % m;
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Numbers/LinearMod.cpp"
#include <vector>
#include <tuple>
#include <cassert>
using namespace std;
using ll = long long;

// for C++14
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }

// ----- LinearMod -----

class LinearMod
{
  vector<ll> A, B, M;

public:
  LinearMod() {}

  void add(ll a, ll b, ll m)
  {
    A.push_back(a);
    B.push_back(b);
    M.push_back(m);
  }

  tuple<ll, ll> get()
  {
    assert(A.size() == B.size() && B.size() == M.size());
    ll x{0}, m{1};
    for (auto i = 0; i < A.size(); i++)
    {
      ll a{A[i] * m};
      ll b{B[i] - A[i] * x};
      ll d{gcd(M[i], a)};
      if (b % d != 0)
      {
        return make_tuple(0, -1);
      }
      ll t{b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d)};
      x = x + m * t;
      m *= M[i] / d;
    }
    return make_tuple(x % m, m);
  }

private:
  static ll extra_gcd(ll a, ll b, ll &x, ll &y)
  {
    ll d{a};
    if (b != 0)
    {
      d = extra_gcd(b, a % b, y, x);
      y -= (a / b) * x;
    }
    else
    {
      x = 1;
      y = 0;
    }
    return d;
  }

  static ll mod_inverse(ll a, ll m)
  {
    ll x, y;
    extra_gcd(a, m, x, y);
    return (m + x % m) % m;
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

