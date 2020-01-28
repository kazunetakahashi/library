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


# :warning: old/under_count.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#149603e6c03516362a8da23f624db945">old</a>
* <a href="{{ site.github.repository_url }}/blob/master/old/under_count.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-09 02:16:51+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
using namespace std;

long long power(long long x, long long n)
{
  if (n == 0)
  {
    return 1;
  }
  else if (n % 2 == 1)
  {
    return (x * power(x, n - 1));
  }
  else
  {
    long long half = power(x, n / 2);
    return (half * half);
  }
}

long long under_count(long long N, long long x)
{
  // N未満の自然数に、xが何個あるか。ただしxは 1 から 9 。
  // Nは10^16くらいまで
  long long ans = 0;
  for (auto i = 0; i < 16; i++)
  {
    ans += N / power(10, i + 1) * power(10, i);
    long long y = N % power(10, i + 1);
    if (power(10, i) * x < y && y <= power(10, i) * (x + 1))
    {
      ans += y - power(10, i) * x;
    }
    else if (power(10, i) * (x + 1) < y)
    {
      ans += power(10, i);
    }
  }
  return ans;
}

int main()
{
  long long N;
  cin >> N;
  cout << under_count(N + 1, 1) << endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "old/under_count.cpp"
#include <iostream>
using namespace std;

long long power(long long x, long long n)
{
  if (n == 0)
  {
    return 1;
  }
  else if (n % 2 == 1)
  {
    return (x * power(x, n - 1));
  }
  else
  {
    long long half = power(x, n / 2);
    return (half * half);
  }
}

long long under_count(long long N, long long x)
{
  // N未満の自然数に、xが何個あるか。ただしxは 1 から 9 。
  // Nは10^16くらいまで
  long long ans = 0;
  for (auto i = 0; i < 16; i++)
  {
    ans += N / power(10, i + 1) * power(10, i);
    long long y = N % power(10, i + 1);
    if (power(10, i) * x < y && y <= power(10, i) * (x + 1))
    {
      ans += y - power(10, i) * x;
    }
    else if (power(10, i) * (x + 1) < y)
    {
      ans += power(10, i);
    }
  }
  return ans;
}

int main()
{
  long long N;
  cin >> N;
  cout << under_count(N + 1, 1) << endl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

