#include <iostream>
#include <vector>
using namespace std;

// ----- BIT -----
// referring to http://hos.ac/slides/20140319_bit.pdf

template <typename T>
class BIT
{
  int N;
  vector<T> data;

public:
  BIT() {}
  BIT(int N) : N{N}, data(N + 1) {}

  void add(int i, T w) // data[i] += w;
  {
    for (; i < N; i |= i + 1)
    {
      data[i] += w;
    }
  }

  void update(int i, T w) // data[i] = w;
  {
    add(i, w - (*this)[i]);
  }

  T sum(int l, int r) // data[l] + \dots + data[r - 1]
  {
    return sum(r) - sum(l);
  }

  T operator[](int i) // data[i]
  {
    return sum(i, i + 1);
  }

private:
  T sum(int i) // data[0] + \dots + data[i - 1]
  {
    T res{0};
    for (--i; i >= 0; i = (i & (i + 1)) - 1)
    {
      res += data[i];
    }
    return res;
  }
};
