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


# :warning: Numbers/EulerNums.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#cbebfa21dbe8e87e788d94a76f073807">Numbers</a>
* <a href="{{ site.github.repository_url }}/blob/master/Numbers/EulerNums.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-02 17:08:46+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// ----- EulerNums -----

class EulerNums
{
  static constexpr ll MAX_SIZE{1000010LL};
  ll N;
  vector<ll> table;

public:
  EulerNums(ll N = MAX_SIZE) : N{N}
  {
    table.resize(N);
    for (auto i = 0; i < N; i++)
    {
      table[i] = i;
    }
    for (auto i = 2; i < N; i++)
    {
      if (table[i] == i)
      {
        for (auto j = i; j < N; j += i)
        {
          table[j] = table[j] / i * (i - 1);
        }
      }
    }
  }

  ll euler(ll n)
  {
    if (n < N)
    {
      return table[N];
    }
    else
    {
      ll res{n};
      for (auto i = 2LL; i * i <= n; i++)
      {
        if (n % i == 0)
        {
          res = res / i * (i - 1);
        }
        for (; n % i == 0; n /= i)
        {
        }
      }
      if (n != 1)
      {
        res = res / n * (n - 1);
      }
      return res;
    }
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Numbers/EulerNums.cpp"
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// ----- EulerNums -----

class EulerNums
{
  static constexpr ll MAX_SIZE{1000010LL};
  ll N;
  vector<ll> table;

public:
  EulerNums(ll N = MAX_SIZE) : N{N}
  {
    table.resize(N);
    for (auto i = 0; i < N; i++)
    {
      table[i] = i;
    }
    for (auto i = 2; i < N; i++)
    {
      if (table[i] == i)
      {
        for (auto j = i; j < N; j += i)
        {
          table[j] = table[j] / i * (i - 1);
        }
      }
    }
  }

  ll euler(ll n)
  {
    if (n < N)
    {
      return table[N];
    }
    else
    {
      ll res{n};
      for (auto i = 2LL; i * i <= n; i++)
      {
        if (n % i == 0)
        {
          res = res / i * (i - 1);
        }
        for (; n % i == 0; n /= i)
        {
        }
      }
      if (n != 1)
      {
        res = res / n * (n - 1);
      }
      return res;
    }
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

