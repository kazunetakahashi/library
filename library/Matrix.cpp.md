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


# :warning: Matrix.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/Matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-24 16:29:17+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// matrix = 2-dim vector
// very tiny library

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;

// ----- Mat and Vec -----

template <typename T = ll>
using Vec = vector<T>;
template <typename T = ll>
using Mat = vector<Vec<T>>;

// operators of Vec / Mat

template <typename T = ll>
Vec<T> operator+(Vec<T> const &A)
{
  return A;
}

template <typename T = ll>
Mat<T> operator+(Mat<T> const &A)
{
  return A;
}

template <typename T = ll>
Vec<T> operator+(Vec<T> const &A, Vec<T> const &B)
{
  assert(A.size() == B.size());
  Vec<T> C(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    C[i] = A[i] + B[i];
  }
  return C;
}

template <typename T = ll>
Mat<T> operator+(Mat<T> const &A, Mat<T> const &B)
{
  assert(A.size() == B.size());
  assert(A[0].size() == B[0].size());
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      C[i][j] += A[i][j] + B[i][j];
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> &operator+=(Vec<T> &A, Vec<T> const &B)
{
  assert(A.size() == B.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    A[i] += B[i];
  }
  return A;
}

template <typename T = ll>
Mat<T> &operator+=(Mat<T> &A, Mat<T> const &B)
{
  assert(A.size() == B.size());
  assert(A[0].size() == B[0].size());
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      A[i][j] += B[i][j];
    }
  }
  return A;
}

template <typename T = ll>
Vec<T> operator-(Vec<T> const &A)
{
  Vec<T> C(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    C[i] = -A[i];
  }
  return C;
}

template <typename T = ll>
Mat<T> operator-(Mat<T> const &A)
{
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      C[i][j] = -A[i][j];
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> operator-(Vec<T> const &A, Vec<T> const &B)
{
  return A + (-B);
}

template <typename T = ll>
Mat<T> operator-(Mat<T> const &A, Mat<T> const &B)
{
  return A + (-B);
}

template <typename T = ll>
Vec<T> &operator-=(Vec<T> &A, Vec<T> const &B)
{
  return A += (-B);
}

template <typename T = ll>
Mat<T> &operator-=(Mat<T> &A, Mat<T> const &B)
{
  return A += (-B);
}

template <typename T = ll>
Vec<T> operator*(T K, Vec<T> const &A)
{
  Vec<T> C(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    C[i] + A[i] * K;
  }
  return C;
}

template <typename T = ll>
Mat<T> operator*(T K, Mat<T> const &A)
{
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      C[i][j] + A[i][j] * K;
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> operator*(Vec<T> const &A, T K)
{
  return K * A;
}

template <typename T = ll>
Mat<T> operator*(Mat<T> const &A, T K)
{
  return K * A;
}

template <typename T = ll>
Vec<T> &operator*=(Vec<T> const &A, T K)
{
  for (auto i = 0u; i < A.size(); i++)
  {
    A[i] *= K;
  }
  return A;
}

template <typename T = ll>
Mat<T> operator*=(Mat<T> const &A, T K)
{
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      A[i][j] *= K;
    }
  }
  return A;
}

template <typename T = ll>
Vec<T> operator/(Vec<T> const &A, T K)
{
  return A * (1 / K);
}

template <typename T = ll>
Mat<T> operator/(Mat<T> const &A, T K)
{
  return A * (1 / K);
}

template <typename T = ll>
Vec<T> &operator/=(Vec<T> &A, T K)
{
  return A *= (1 / K);
}

template <typename T = ll>
Mat<T> &operator/=(Mat<T> &A, T K)
{
  return A *= (1 / K);
}

// multiply operators

template <typename T = ll>
Mat<T> operator*(Mat<T> const &A, Mat<T> const &B)
{
  assert(A[0].size() == B.size());
  Mat<T> C(A.size(), Vec<T>(B[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < B[0].size(); j++)
    {
      for (auto k = 0u; k < A[0].size(); k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> operator*(Mat<T> const &A, Vec<T> const &V)
{
  assert(A[0].size() == V.size());
  Vec<T> W(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0; j < A[0].size(); j++)
    {
      W[i] += A[i][j] * V[j];
    }
  }
  return W;
}

template <typename T = ll>
Mat<T> power(Mat<T> const &A, ll N)
{
  assert(A.size() == A[0].size());
  Mat<T> B(A.size(), Vec(A.size(), 1));
  while (N > 0)
  {
    if (N & 1)
    {
      B *= A;
    }
    A *= A;
    N >>= 1;
  }
  return B;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Matrix.cpp"
// matrix = 2-dim vector
// very tiny library

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;

// ----- Mat and Vec -----

template <typename T = ll>
using Vec = vector<T>;
template <typename T = ll>
using Mat = vector<Vec<T>>;

// operators of Vec / Mat

template <typename T = ll>
Vec<T> operator+(Vec<T> const &A)
{
  return A;
}

template <typename T = ll>
Mat<T> operator+(Mat<T> const &A)
{
  return A;
}

template <typename T = ll>
Vec<T> operator+(Vec<T> const &A, Vec<T> const &B)
{
  assert(A.size() == B.size());
  Vec<T> C(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    C[i] = A[i] + B[i];
  }
  return C;
}

template <typename T = ll>
Mat<T> operator+(Mat<T> const &A, Mat<T> const &B)
{
  assert(A.size() == B.size());
  assert(A[0].size() == B[0].size());
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      C[i][j] += A[i][j] + B[i][j];
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> &operator+=(Vec<T> &A, Vec<T> const &B)
{
  assert(A.size() == B.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    A[i] += B[i];
  }
  return A;
}

template <typename T = ll>
Mat<T> &operator+=(Mat<T> &A, Mat<T> const &B)
{
  assert(A.size() == B.size());
  assert(A[0].size() == B[0].size());
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      A[i][j] += B[i][j];
    }
  }
  return A;
}

template <typename T = ll>
Vec<T> operator-(Vec<T> const &A)
{
  Vec<T> C(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    C[i] = -A[i];
  }
  return C;
}

template <typename T = ll>
Mat<T> operator-(Mat<T> const &A)
{
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      C[i][j] = -A[i][j];
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> operator-(Vec<T> const &A, Vec<T> const &B)
{
  return A + (-B);
}

template <typename T = ll>
Mat<T> operator-(Mat<T> const &A, Mat<T> const &B)
{
  return A + (-B);
}

template <typename T = ll>
Vec<T> &operator-=(Vec<T> &A, Vec<T> const &B)
{
  return A += (-B);
}

template <typename T = ll>
Mat<T> &operator-=(Mat<T> &A, Mat<T> const &B)
{
  return A += (-B);
}

template <typename T = ll>
Vec<T> operator*(T K, Vec<T> const &A)
{
  Vec<T> C(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    C[i] + A[i] * K;
  }
  return C;
}

template <typename T = ll>
Mat<T> operator*(T K, Mat<T> const &A)
{
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      C[i][j] + A[i][j] * K;
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> operator*(Vec<T> const &A, T K)
{
  return K * A;
}

template <typename T = ll>
Mat<T> operator*(Mat<T> const &A, T K)
{
  return K * A;
}

template <typename T = ll>
Vec<T> &operator*=(Vec<T> const &A, T K)
{
  for (auto i = 0u; i < A.size(); i++)
  {
    A[i] *= K;
  }
  return A;
}

template <typename T = ll>
Mat<T> operator*=(Mat<T> const &A, T K)
{
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < A[0].size(); j++)
    {
      A[i][j] *= K;
    }
  }
  return A;
}

template <typename T = ll>
Vec<T> operator/(Vec<T> const &A, T K)
{
  return A * (1 / K);
}

template <typename T = ll>
Mat<T> operator/(Mat<T> const &A, T K)
{
  return A * (1 / K);
}

template <typename T = ll>
Vec<T> &operator/=(Vec<T> &A, T K)
{
  return A *= (1 / K);
}

template <typename T = ll>
Mat<T> &operator/=(Mat<T> &A, T K)
{
  return A *= (1 / K);
}

// multiply operators

template <typename T = ll>
Mat<T> operator*(Mat<T> const &A, Mat<T> const &B)
{
  assert(A[0].size() == B.size());
  Mat<T> C(A.size(), Vec<T>(B[0].size()));
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0u; j < B[0].size(); j++)
    {
      for (auto k = 0u; k < A[0].size(); k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

template <typename T = ll>
Vec<T> operator*(Mat<T> const &A, Vec<T> const &V)
{
  assert(A[0].size() == V.size());
  Vec<T> W(A.size());
  for (auto i = 0u; i < A.size(); i++)
  {
    for (auto j = 0; j < A[0].size(); j++)
    {
      W[i] += A[i][j] * V[j];
    }
  }
  return W;
}

template <typename T = ll>
Mat<T> power(Mat<T> const &A, ll N)
{
  assert(A.size() == A[0].size());
  Mat<T> B(A.size(), Vec(A.size(), 1));
  while (N > 0)
  {
    if (N & 1)
    {
      B *= A;
    }
    A *= A;
    N >>= 1;
  }
  return B;
}

```
{% endraw %}

<a href="../index.html">Back to top page</a>

