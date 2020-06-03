#include <vector>
#include <cassert>
using namespace std;

// ----- Permutation -----

struct Permutation
{
  vector<int> V;

  Permutation() {}
  Permutation(vector<int> const &V) : V{V} {}

  static Permutation unit(size_t N)
  {
    vector<int> X(N);
    for (auto i = 0; i < static_cast<int>(N); ++i)
    {
      X[i] = i;
    }
    return Permutation{X};
  }

  size_t size() const { return V.size(); }
  int operator[](size_t i) const { return V[i]; }

  Permutation inverse() const
  {
    vector<int> Q(size());
    for (auto i = 0; i < static_cast<int>(size()); ++i)
    {
      Q[(*this)[i]] = i;
    }
    return Permutation{Q};
  }

  Permutation operator*(Permutation const &Q) const
  {
    assert(size() == Q.size());
    vector<int> R(size());
    for (auto i = 0; i < static_cast<int>(size()); ++i)
    {
      R[i] = (*this)[Q[i]];
    }
    return Permutation{R};
  }

  Permutation &operator*=(Permutation const &Q)
  {
    return *this = *this * Q;
  }

  Permutation power(int n)
  {
    if (n == 0)
    {
      return unit(size());
    }
    if (n & 1)
    {
      auto W{power(n / 2)};
      return W * W;
    }
    return *this * power(n - 1);
  }
};
