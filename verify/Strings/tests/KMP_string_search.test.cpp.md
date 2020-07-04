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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: Strings/tests/KMP_string_search.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#57d4581aaf4a3eff76a11de483c97ff2">Strings/tests</a>
* <a href="{{ site.github.repository_url }}/blob/master/Strings/tests/KMP_string_search.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-05 05:56:11+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/Strings/KMP.cpp.html">Strings/KMP.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "../KMP.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

int main()
{
  string t, p;
  cin >> t >> p;
  MP<string> mp{p};
  for (auto e : mp.place(t))
  {
    cout << e << endl;
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Strings/KMP.cpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ----- MP algorithm -----

template <typename Type = string>
class MP
{
  int N;
  Type S;
  vector<int> A;

public:
  MP() {}
  MP(Type const &S) : N(S.size()), S{S}, A(N + 1, -1)
  {
    int j{-1};
    for (auto i{0}; i < N; i++)
    {
      while (j != -1 && S[j] != S[i])
      {
        j = A[j];
      }
      ++j;
      A[i + 1] = j;
    }
  }

  int operator[](int i) const { return A[i]; }

  int period(int i) const
  { // The period of S[0, i).
    auto tmp{i - A[i]};
    if (i % tmp == 0)
    {
      return tmp;
    }
    return i;
  }

  vector<int> place(Type const &T) const
  {
    vector<int> res;
    int j{0};
    for (auto i{size_t{0}}; i < T.size(); i++)
    {
      while (j != -1 && S[j] != T[i])
      {
        j = A[j];
      }
      ++j;
      if (j == N)
      {
        res.push_back(i - j + 1);
        j = A[j];
      }
    }
    return res;
  }

  vector<bool> table(Type const &T) const
  {
    vector<bool> res(T.size(), false);
    for (auto e : place(T))
    {
      res[e] = true;
    }
    return res;
  }
};
#line 2 "Strings/tests/KMP_string_search.test.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

int main()
{
  string t, p;
  cin >> t >> p;
  MP<string> mp{p};
  for (auto e : mp.place(t))
  {
    cout << e << endl;
  }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

