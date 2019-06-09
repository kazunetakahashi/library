#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

template <class T>
class Matrix
{
private:
  int H, W;
  T **a;

public:
  Matrix() {}

  Matrix(int h, int w) : H(h), W(w)
  {
    a = new T *[H];
    for (auto i = 0; i < H; i++)
    {
      a[i] = new T[W];
    }
  }

  Matrix(const Matrix &A)
  {
    H = A.H;
    W = A.W;
    a = new T *[H];
    for (auto i = 0; i < H; i++)
    {
      a[i] = new T[W];
    }
    for (auto i = 0; i < H; i++)
    {
      for (auto j = 0; j < W; j++)
      {
        a[i][j] = A.a[i][j];
      }
    }
  }

  Matrix &operator=(const Matrix A)
  {
    H = A.H;
    W = A.W;
    a = new T *[H];
    for (auto i = 0; i < H; i++)
    {
      a[i] = new T[W];
    }
    for (auto i = 0; i < H; i++)
    {
      for (auto j = 0; j < W; j++)
      {
        a[i][j] = A.a[i][j];
      }
    }
    return *this;
  }

  Matrix &operator=(const vector<T> v)
  {
    assert((int)v.size() == H * W);
    for (auto i = 0; i < H; i++)
    {
      for (auto j = 0; j < W; j++)
      {
        a[i][j] = v[i * W + j];
      }
    }
    return *this;
  }

  const Matrix operator-() const
  {
    Matrix X(H, W);
    for (auto i = 0; i < H; i++)
    {
      for (auto j = 0; j < W; j++)
      {
        X.a[i][j] = -a[i][j];
      }
    }
    return X;
  }

  const Matrix operator+(const Matrix &A) const
  {
    assert(A.H == H);
    assert(A.W == W);
    Matrix X(H, W);
    for (auto i = 0; i < H; i++)
    {
      for (auto j = 0; j < W; j++)
      {
        X.a[i][j] = a[i][j] + A.a[i][j];
      }
    }
    return X;
  }

  const Matrix operator-(const Matrix &A) const
  {
    return this + (-A);
  }

  const Matrix operator*(const Matrix &A) const
  {
    assert(W == A.H);
    Matrix X(H, A.W);
    for (auto i = 0; i < X.H; i++)
    {
      for (auto j = 0; j < X.W; j++)
      {
        X.a[i][j] = 0;
        for (auto k = 0; k < W; k++)
        {
          T t = a[i][k] * A.a[k][j];
          X.a[i][j] += t;
        }
      }
    }
    return X;
  }

  Matrix &operator+=(const Matrix &A)
  {
    Matrix X = this + A;
    this = X;
    return this;
  }

  Matrix &operator-=(const Matrix &A)
  {
    return this += (-A);
  }

  Matrix &operator*=(const Matrix &A)
  {
    Matrix X = this * A;
    this = X;
    return this;
  }

  bool operator==(const Matrix &A) const
  {
    assert(H == A.H);
    assert(W == A.W);
    for (auto i = 0; i < H; i++)
    {
      for (auto j = 0; j < W; j++)
      {
        if (a[i][j] != A.a[i][j])
        {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix &A) const
  {
    return !(this == A);
  }

  const T *&operator[](const size_t i) const
  {
    return a[i];
  }

  T *&operator[](const size_t i)
  {
    return a[i];
  }

  const Matrix power(ll N) const
  {
    assert(H == W);
    // N > 0
    if (N == 1)
    {
      return *this;
    }
    if (N % 2 == 1)
    {
      return power(N - 1) * (*this);
    }
    Matrix X = power(N / 2);
    return X * X;
  }
};
