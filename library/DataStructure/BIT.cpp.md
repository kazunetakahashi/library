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


# :heavy_check_mark: DataStructure/BIT.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/BIT.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 07:42:19+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/DataStructure/tests/BIT.test.cpp.html">DataStructure/tests/BIT.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <vector>
using namespace std;

// ----- BIT -----
// referring to http://hos.ac/slides/20140319_bit.pdf

template <typename T>
class BIT
{
  int N;
  vector<T> data;

public:
  BIT() {}
  BIT(int N) : N{N}, data(N + 1) {}

  void add(int i, T w) // data[i] += w;
  {
    for (; i < N; i |= i + 1)
    {
      data[i] += w;
    }
  }

  void update(int i, T w) // data[i] = w;
  {
    add(i, w - (*this)[i]);
  }

  T sum(int l, int r) // data[l] + \dots + data[r - 1]
  {
    return sum(r) - sum(l);
  }

  T operator[](int i) // data[i]
  {
    return sum(i, i + 1);
  }

private:
  T sum(int i) // data[0] + \dots + data[i - 1]
  {
    T res{0};
    for (--i; i >= 0; i = (i & (i + 1)) - 1)
    {
      res += data[i];
    }
    return res;
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/BIT.cpp"
#include <iostream>
#include <vector>
using namespace std;

// ----- BIT -----
// referring to http://hos.ac/slides/20140319_bit.pdf

template <typename T>
class BIT
{
  int N;
  vector<T> data;

public:
  BIT() {}
  BIT(int N) : N{N}, data(N + 1) {}

  void add(int i, T w) // data[i] += w;
  {
    for (; i < N; i |= i + 1)
    {
      data[i] += w;
    }
  }

  void update(int i, T w) // data[i] = w;
  {
    add(i, w - (*this)[i]);
  }

  T sum(int l, int r) // data[l] + \dots + data[r - 1]
  {
    return sum(r) - sum(l);
  }

  T operator[](int i) // data[i]
  {
    return sum(i, i + 1);
  }

private:
  T sum(int i) // data[0] + \dots + data[i - 1]
  {
    T res{0};
    for (--i; i >= 0; i = (i & (i + 1)) - 1)
    {
      res += data[i];
    }
    return res;
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

