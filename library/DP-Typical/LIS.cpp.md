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


# :heavy_check_mark: DP-Typical/LIS.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5b6c359dc823363bb7722835b7b24d01">DP-Typical</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP-Typical/LIS.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-02 20:09:49+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/DP-Typical/tests/LIS.test.cpp.html">DP-Typical/tests/LIS.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>
using namespace std;
using ll = long long;

// ----- LIS -----

template <typename T>
class LIS
{
  struct Cache_LIS
  {
    typename vector<T>::iterator it;
    T value;
  };

  int n; // fixed
  T infty;
  vector<T> dp;
  stack<Cache_LIS> st;

public:
  LIS() {}
  LIS(int n, T infty = numeric_limits<T>::max()) : n{n}, infty{infty}, dp(n, infty) {}

  int query(T a)
  {
    auto it{lower_bound(dp.begin(), dp.end(), a)};
    auto value{*it};
    st.push(Cache_LIS{it, value});
    *it = a;
    return lower_bound(dp.begin(), dp.end(), infty) - dp.begin();
  }

  bool rollback()
  {
    if (st.empty())
    {
      return false;
    }
    auto const &c{st.top()};
    *c.it = c.value;
    st.pop();
    return true;
  }

private:
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP-Typical/LIS.cpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>
using namespace std;
using ll = long long;

// ----- LIS -----

template <typename T>
class LIS
{
  struct Cache_LIS
  {
    typename vector<T>::iterator it;
    T value;
  };

  int n; // fixed
  T infty;
  vector<T> dp;
  stack<Cache_LIS> st;

public:
  LIS() {}
  LIS(int n, T infty = numeric_limits<T>::max()) : n{n}, infty{infty}, dp(n, infty) {}

  int query(T a)
  {
    auto it{lower_bound(dp.begin(), dp.end(), a)};
    auto value{*it};
    st.push(Cache_LIS{it, value});
    *it = a;
    return lower_bound(dp.begin(), dp.end(), infty) - dp.begin();
  }

  bool rollback()
  {
    if (st.empty())
    {
      return false;
    }
    auto const &c{st.top()};
    *c.it = c.value;
    st.pop();
    return true;
  }

private:
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

