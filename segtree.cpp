#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

//----------------------------------

template <class T>
class SegTree
{ // 0-indexed, [0, N).
private:
  int N;
  T *dat;
  T UNIT; // モノイドの単位元

  static T func(T x, T y)
  { // ここで演算を定義する。圏、特にモノイドであればなんでも良い。
    // 実装はモノイドであるとする。
    // return min(x, y);
    return x + y;
  }

  static T _update(T x, T y)
  { // update で 値をどうするかを書く。
    // return y;
    return func(x, y);
  }

public:
  SegTree() {}

  SegTree(int n, T unit)
  { // ここで unit を定義するのも変な実装だけどめんどいからこれでいい。
    // min の場合は INFTY = (1LL << 60)
    // + の場合は 0 とする。
    UNIT = unit;
    N = 1;
    while (N < n)
    {
      N *= 2;
    }
    dat = new T[2 * N - 1];
    for (auto i = 0; i < 2 * N - 1; ++i)
    {
      dat[i] = UNIT;
    }
  }

  void update(int k, T a)
  {
    k += N - 1;
    dat[k] = _update(dat[k], a);
    while (k > 0)
    {
      k = (k - 1) / 2;
      dat[k] = func(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

private:
  T find(int a, int b, int k, int l, int r)
  {
    if (r <= a || b <= l)
      return UNIT;
    if (a <= l && r <= b)
      return dat[k];
    T vl = find(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = find(a, b, k * 2 + 2, (l + r) / 2, r);
    return func(vl, vr);
  }

public:
  T find(int a, int b)
  { // [a, b) の find をする。
    return find(a, b, 0, 0, N);
  }
};

//----------------------------------

int main()
{
}