#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// ----- Mint -----

ll MOD{998244353LL}; // This is dummy. This is needed for global declearation.
constexpr ll MAX_SIZE{300010LL};

/*
  Slow manipulations:
    - Mint power(ll N) const
    - Mint &operator/=(Mint const &a)
    - Mint operator/(Mint const &a)
  Instead of using these, consider using for-loop and base
  e.g.
    mint base{1};
    for (auto j = MOD - 1; j >= 0; j--)
    {
      ans[j] -= base * C(MOD - 1, j);
      base *= -i;
    }
*/

class Mint
{
public:
  ll x;
  Mint() : x{0LL} {}
  Mint(ll x) : x{(x % MOD + MOD) % MOD} {}
  Mint operator-() const { return x ? MOD - x : 0; }
  Mint &operator+=(Mint const &a)
  {
    if ((x += a.x) >= MOD)
    {
      x -= MOD;
    }
    return *this;
  }
  Mint &operator-=(Mint const &a) { return *this += -a; }
  Mint &operator++() { return *this += 1; }
  Mint operator++(int)
  {
    Mint tmp{*this};
    ++*this;
    return tmp;
  }
  Mint &operator--() { return *this -= 1; }
  Mint operator--(int)
  {
    Mint tmp{*this};
    --*this;
    return tmp;
  }
  Mint &operator*=(Mint const &a)
  {
    (x *= a.x) %= MOD;
    return *this;
  }
  Mint &operator/=(Mint const &a)
  {
    Mint b{a};
    return *this *= b.power(MOD - 2);
  }
  Mint operator+(Mint const &a) const { return Mint(*this) += a; }
  Mint operator-(Mint const &a) const { return Mint(*this) -= a; }
  Mint operator*(Mint const &a) const { return Mint(*this) *= a; }
  Mint operator/(Mint const &a) const { return Mint(*this) /= a; }
  bool operator<(Mint const &a) const { return x < a.x; }
  bool operator<=(Mint const &a) const { return x <= a.x; }
  bool operator>(Mint const &a) const { return x > a.x; }
  bool operator>=(Mint const &a) const { return x >= a.x; }
  bool operator==(Mint const &a) const { return x == a.x; }
  bool operator!=(Mint const &a) const { return !(*this == a); }
  Mint power(ll N) const
  {
    if (N == 0)
    {
      return 1;
    }
    else if (N % 2 == 1)
    {
      return *this * power(N - 1);
    }
    else
    {
      Mint half = power(N / 2);
      return half * half;
    }
  }
};
Mint operator+(ll lhs, Mint const &rhs)
{
  return rhs + lhs;
}
Mint operator-(ll lhs, Mint const &rhs)
{
  return -rhs + lhs;
}
Mint operator*(ll lhs, Mint const &rhs)
{
  return rhs * lhs;
}
Mint operator/(ll lhs, Mint const &rhs)
{
  return Mint{lhs} / rhs;
}
istream &operator>>(istream &stream, Mint &a)
{
  return stream >> a.x;
}
ostream &operator<<(ostream &stream, Mint const &a)
{
  return stream << a.x;
}
// ----- Combination -----
class Combination
{
public:
  vector<Mint> inv, fact, factinv;
  Combination() : inv(MAX_SIZE), fact(MAX_SIZE), factinv(MAX_SIZE)
  {
    inv[1] = 1;
    for (auto i = 2LL; i < MAX_SIZE; i++)
    {
      inv[i] = (-inv[MOD % i]) * (MOD / i);
    }
    fact[0] = factinv[0] = 1;
    for (auto i = 1LL; i < MAX_SIZE; i++)
    {
      fact[i] = Mint(i) * fact[i - 1];
      factinv[i] = inv[i] * factinv[i - 1];
    }
  }
  Mint operator()(int n, int k)
  {
    if (n >= 0 && k >= 0 && n - k >= 0)
    {
      return fact[n] * factinv[k] * factinv[n - k];
    }
    return 0;
  }
  Mint catalan(int x, int y)
  {
    return (*this)(x + y, y) - (*this)(x + y, y - 1);
  }
};
