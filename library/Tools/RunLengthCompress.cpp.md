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


# :warning: Tools/RunLengthCompress.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8625e1de7be14c39b1d14dc03d822497">Tools</a>
* <a href="{{ site.github.repository_url }}/blob/master/Tools/RunLengthCompress.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-08 00:00:50+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <tuple>
#include <vector>
using namespace std;

// ----- RunLengthCompress -----

template <typename T>
auto RunLengthCompress(T const &S) -> vector<tuple<remove_const_t<remove_reference_t<decltype(S[0])>>, int>>
{
  using U = remove_const_t<remove_reference_t<decltype(S[0])>>;
  vector<tuple<U, int>> res;
  U c{S[0]};
  int x{0};
  for (auto e : S)
  {
    if (c == e)
    {
      ++x;
    }
    else
    {
      res.emplace_back(c, x);
      c = e;
      x = 1;
    }
  }
  res.emplace_back(c, x);
  return res;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Tools/RunLengthCompress.cpp"
#include <tuple>
#include <vector>
using namespace std;

// ----- RunLengthCompress -----

template <typename T>
auto RunLengthCompress(T const &S) -> vector<tuple<remove_const_t<remove_reference_t<decltype(S[0])>>, int>>
{
  using U = remove_const_t<remove_reference_t<decltype(S[0])>>;
  vector<tuple<U, int>> res;
  U c{S[0]};
  int x{0};
  for (auto e : S)
  {
    if (c == e)
    {
      ++x;
    }
    else
    {
      res.emplace_back(c, x);
      c = e;
      x = 1;
    }
  }
  res.emplace_back(c, x);
  return res;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

