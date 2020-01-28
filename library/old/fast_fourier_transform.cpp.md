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


# :warning: old/fast_fourier_transform.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#149603e6c03516362a8da23f624db945">old</a>
* <a href="{{ site.github.repository_url }}/blob/master/old/fast_fourier_transform.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-09 02:16:51+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <complex>
#include <vector>
using namespace std;

const int N = (1 << 18); // 最大次数
const double PI = acos(-1);
typedef complex<double> comp;

vector<comp> dft(vector<comp> f, int n, bool doesinv)
{
  if (n == 1)
    return f;
  vector<comp> f0, f1;
  for (auto i = 0; i < n / 2; i++)
  {
    f0.push_back(f[2 * i]);
    f1.push_back(f[2 * i + 1]);
  }
  f0 = dft(f0, n / 2, doesinv);
  f1 = dft(f1, n / 2, doesinv);
  comp zeta;
  if (!doesinv)
  {
    zeta = comp(cos(2 * PI / n), sin(2 * PI / n));
  }
  else
  {
    zeta = comp(cos(2 * PI / n), -1 * sin(2 * PI / n));
  }
  comp pow_zeta = comp(1, 0);
  for (auto i = 0; i < n; i++)
  {
    f[i] = f0[i % (n / 2)] + pow_zeta * f1[i % (n / 2)];
    pow_zeta = pow_zeta * zeta;
  }
  return f;
}

vector<comp> multiply(vector<comp> g, vector<comp> h)
{
  vector<comp> gg = dft(g, N, false);
  vector<comp> hh = dft(h, N, false);
  vector<comp> ff = vector<comp>(N);
  for (auto i = 0; i < N; i++)
  {
    ff[i] = gg[i] * hh[i];
  }
  vector<comp> ans = dft(ff, N, true);
  for (auto i = 0; i < N; i++)
  {
    ans[i] = ans[i] / comp(N, 0);
  }
  return ans;
}

int main()
{
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "old/fast_fourier_transform.cpp"
#include <iostream>
#include <complex>
#include <vector>
using namespace std;

const int N = (1 << 18); // 最大次数
const double PI = acos(-1);
typedef complex<double> comp;

vector<comp> dft(vector<comp> f, int n, bool doesinv)
{
  if (n == 1)
    return f;
  vector<comp> f0, f1;
  for (auto i = 0; i < n / 2; i++)
  {
    f0.push_back(f[2 * i]);
    f1.push_back(f[2 * i + 1]);
  }
  f0 = dft(f0, n / 2, doesinv);
  f1 = dft(f1, n / 2, doesinv);
  comp zeta;
  if (!doesinv)
  {
    zeta = comp(cos(2 * PI / n), sin(2 * PI / n));
  }
  else
  {
    zeta = comp(cos(2 * PI / n), -1 * sin(2 * PI / n));
  }
  comp pow_zeta = comp(1, 0);
  for (auto i = 0; i < n; i++)
  {
    f[i] = f0[i % (n / 2)] + pow_zeta * f1[i % (n / 2)];
    pow_zeta = pow_zeta * zeta;
  }
  return f;
}

vector<comp> multiply(vector<comp> g, vector<comp> h)
{
  vector<comp> gg = dft(g, N, false);
  vector<comp> hh = dft(h, N, false);
  vector<comp> ff = vector<comp>(N);
  for (auto i = 0; i < N; i++)
  {
    ff[i] = gg[i] * hh[i];
  }
  vector<comp> ans = dft(ff, N, true);
  for (auto i = 0; i < N; i++)
  {
    ans[i] = ans[i] / comp(N, 0);
  }
  return ans;
}

int main()
{
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

