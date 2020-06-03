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
  for (auto i = size_t{0}; i < A.size(); i++)
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
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    for (auto j = size_t{0}; j < A[0].size(); j++)
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
  for (auto i = size_t{0}; i < A.size(); i++)
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
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    for (auto j = size_t{0}; j < A[0].size(); j++)
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
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    C[i] = -A[i];
  }
  return C;
}

template <typename T = ll>
Mat<T> operator-(Mat<T> const &A)
{
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    for (auto j = size_t{0}; j < A[0].size(); j++)
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
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    C[i] + A[i] * K;
  }
  return C;
}

template <typename T = ll>
Mat<T> operator*(T K, Mat<T> const &A)
{
  Mat<T> C(A.size(), Vec<T>(A[0].size()));
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    for (auto j = size_t{0}; j < A[0].size(); j++)
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
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    A[i] *= K;
  }
  return A;
}

template <typename T = ll>
Mat<T> operator*=(Mat<T> const &A, T K)
{
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    for (auto j = size_t{0}; j < A[0].size(); j++)
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

// generator of unit matrix
// call example: Mat<T> A{unit_matrix<T>(s)};

template <typename T = ll>
Mat<T> unit_matrix(size_t s)
{
  Mat<T> res(s, Vec<T>(s, T{0}));
  for (auto i = size_t{0}; i < s; ++i)
  {
    res[i][i] = T{1};
  }
  return res;
}

// multiply operators

template <typename T = ll>
Mat<T> operator*(Mat<T> const &A, Mat<T> const &B)
{
  assert(A[0].size() == B.size());
  Mat<T> C(A.size(), Vec<T>(B[0].size()));
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    for (auto j = size_t{0}; j < B[0].size(); j++)
    {
      for (auto k = size_t{0}; k < A[0].size(); k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

template <typename T = ll>
Mat<T> &operator*=(Mat<T> &A, Mat<T> const &B)
{
  auto C{A * B};
  return A = C;
}

template <typename T = ll>
Vec<T> operator*(Mat<T> const &A, Vec<T> const &V)
{
  assert(A[0].size() == V.size());
  Vec<T> W(A.size());
  for (auto i = size_t{0}; i < A.size(); i++)
  {
    for (auto j = size_t{0}; j < A[0].size(); j++)
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
  if (N == 0)
  {
    return unit_matrix<T>(A.size());
  }
  if (N & 1)
  {
    return A * power(A, N - 1);
  }
  auto B{power(A, N / 2)};
  return B * B;
}
