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


# :warning: ZAlgorithm.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/ZAlgorithm.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-11 03:07:30+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ----- ZAlgorithm -----
// from drken-san: http://drken1215.hatenablog.com/entry/2019/09/16/014600

template <typename Type = string>
class ZAlgorithm
{
  int N;
  Type S;
  vector<int> V;

public:
  ZAlgorithm() {}
  ZAlgorithm(Type const &S) : N{static_cast<int>(S.size())}, S{S}, V(N)
  {
    V[0] = N;
    int i{1}, j{0};
    while (i < N)
    {
      while (i + j < N && S[j] == S[i + j])
      {
        ++j;
      }
      V[i] = j;
      if (j == 0)
      {
        ++i;
        continue;
      }
      int k{1};
      while (i + k < N && k + V[k] < j)
      {
        V[i + k] = V[k];
        ++k;
      }
      i += k;
      j -= k;
    }
  }

  int operator[](int i) const
  {
    return V[i];
  }
};

// https://atcoder.jp/contests/abc141/tasks/abc141_e

int main()
{
  int N;
  string S;
  cin >> N >> S;
  int ans{0};
  for (int i = 0; i < N; ++i)
  {
    string T{S.substr(i)};
    ZAlgorithm<string> Z(T);
    for (int j = 0; j < static_cast<int>(T.size()); ++j)
    {
      ans = max(ans, min(Z[j], j));
    }
  }
  cout << ans << endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "ZAlgorithm.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ----- ZAlgorithm -----
// from drken-san: http://drken1215.hatenablog.com/entry/2019/09/16/014600

template <typename Type = string>
class ZAlgorithm
{
  int N;
  Type S;
  vector<int> V;

public:
  ZAlgorithm() {}
  ZAlgorithm(Type const &S) : N{static_cast<int>(S.size())}, S{S}, V(N)
  {
    V[0] = N;
    int i{1}, j{0};
    while (i < N)
    {
      while (i + j < N && S[j] == S[i + j])
      {
        ++j;
      }
      V[i] = j;
      if (j == 0)
      {
        ++i;
        continue;
      }
      int k{1};
      while (i + k < N && k + V[k] < j)
      {
        V[i + k] = V[k];
        ++k;
      }
      i += k;
      j -= k;
    }
  }

  int operator[](int i) const
  {
    return V[i];
  }
};

// https://atcoder.jp/contests/abc141/tasks/abc141_e

int main()
{
  int N;
  string S;
  cin >> N >> S;
  int ans{0};
  for (int i = 0; i < N; ++i)
  {
    string T{S.substr(i)};
    ZAlgorithm<string> Z(T);
    for (int j = 0; j < static_cast<int>(T.size()); ++j)
    {
      ans = max(ans, min(Z[j], j));
    }
  }
  cout << ans << endl;
}

```
{% endraw %}

<a href="../index.html">Back to top page</a>

