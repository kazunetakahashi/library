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


# :warning: Math/Permutation.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#a49950aa047c2292e989e368a97a3aae">Math</a>
* <a href="{{ site.github.repository_url }}/blob/master/Math/Permutation.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-04 00:13:06+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>
#include <cassert>
using namespace std;

// ----- Permutation -----

struct Permutation
{
  vector<int> V;

  Permutation() {}
  Permutation(vector<int> const &V) : V{V} {}

  static Permutation unit(size_t N)
  {
    vector<int> X(N);
    for (auto i = 0; i < static_cast<int>(N); ++i)
    {
      X[i] = i;
    }
    return Permutation{X};
  }

  size_t size() const { return V.size(); }
  int operator[](size_t i) const { return V[i]; }

  Permutation inverse() const
  {
    vector<int> Q(size());
    for (auto i = 0; i < static_cast<int>(size()); ++i)
    {
      Q[(*this)[i]] = i;
    }
    return Permutation{Q};
  }

  Permutation operator*(Permutation const &Q) const
  {
    assert(size() == Q.size());
    vector<int> R(size());
    for (auto i = 0; i < static_cast<int>(size()); ++i)
    {
      R[i] = (*this)[Q[i]];
    }
    return Permutation{R};
  }

  Permutation &operator*=(Permutation const &Q)
  {
    return *this = *this * Q;
  }

  Permutation power(int n)
  {
    if (n == 0)
    {
      return unit(size());
    }
    if (n & 1)
    {
      auto W{power(n / 2)};
      return W * W;
    }
    return *this * power(n - 1);
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Math/Permutation.cpp"
#include <vector>
#include <cassert>
using namespace std;

// ----- Permutation -----

struct Permutation
{
  vector<int> V;

  Permutation() {}
  Permutation(vector<int> const &V) : V{V} {}

  static Permutation unit(size_t N)
  {
    vector<int> X(N);
    for (auto i = 0; i < static_cast<int>(N); ++i)
    {
      X[i] = i;
    }
    return Permutation{X};
  }

  size_t size() const { return V.size(); }
  int operator[](size_t i) const { return V[i]; }

  Permutation inverse() const
  {
    vector<int> Q(size());
    for (auto i = 0; i < static_cast<int>(size()); ++i)
    {
      Q[(*this)[i]] = i;
    }
    return Permutation{Q};
  }

  Permutation operator*(Permutation const &Q) const
  {
    assert(size() == Q.size());
    vector<int> R(size());
    for (auto i = 0; i < static_cast<int>(size()); ++i)
    {
      R[i] = (*this)[Q[i]];
    }
    return Permutation{R};
  }

  Permutation &operator*=(Permutation const &Q)
  {
    return *this = *this * Q;
  }

  Permutation power(int n)
  {
    if (n == 0)
    {
      return unit(size());
    }
    if (n & 1)
    {
      auto W{power(n / 2)};
      return W * W;
    }
    return *this * power(n - 1);
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

