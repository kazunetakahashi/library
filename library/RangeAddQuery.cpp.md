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


# :warning: RangeAddQuery.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/RangeAddQuery.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 14:29:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

template <typename T = ll>
class RangeAddQuery
{ // index starts at 0.
  int N;
  vector<T> data;

public:
  RangeAddQuery(int N) : N{N}, data(N + 1, T{0}) {}

  T get(int i)
  {
    return _sum(i + 1);
  }

  void add(int a, int b, T x)
  { // [a, b)
    _add(a + 1, x);
    _add(b + 1, -x);
  }

private:
  T _sum(int i)
  { // [1, i]
    T s{0};
    while (i > 0)
    {
      s += data[i];
      i -= i & -i;
    }
    return s;
  }

  void _add(int i, ll x)
  {
    while (i <= N)
    {
      data[i] += x;
      i += i & -i;
    }
  }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja

int main()
{
  int N, Q;
  cin >> N >> Q;
  RangeAddQuery<ll> RAQ(N);
  for (auto i = 0; i < Q; ++i)
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
      RAQ.add(s, t + 1, x);
    }
    else
    {
      int i;
      cin >> i;
      --i;
      cout << RAQ.get(i) << endl;
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "RangeAddQuery.cpp"
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

template <typename T = ll>
class RangeAddQuery
{ // index starts at 0.
  int N;
  vector<T> data;

public:
  RangeAddQuery(int N) : N{N}, data(N + 1, T{0}) {}

  T get(int i)
  {
    return _sum(i + 1);
  }

  void add(int a, int b, T x)
  { // [a, b)
    _add(a + 1, x);
    _add(b + 1, -x);
  }

private:
  T _sum(int i)
  { // [1, i]
    T s{0};
    while (i > 0)
    {
      s += data[i];
      i -= i & -i;
    }
    return s;
  }

  void _add(int i, ll x)
  {
    while (i <= N)
    {
      data[i] += x;
      i += i & -i;
    }
  }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja

int main()
{
  int N, Q;
  cin >> N >> Q;
  RangeAddQuery<ll> RAQ(N);
  for (auto i = 0; i < Q; ++i)
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
      RAQ.add(s, t + 1, x);
    }
    else
    {
      int i;
      cin >> i;
      --i;
      cout << RAQ.get(i) << endl;
    }
  }
}

```
{% endraw %}

<a href="../index.html">Back to top page</a>

