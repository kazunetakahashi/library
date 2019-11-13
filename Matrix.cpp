// matrix = 2-dim vector
// very tiny library

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;

// ----- Mat and Vec

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
