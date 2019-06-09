#include <iostream>
using namespace std;

typedef long long ll;

const int MAX_SIZE = 1000010;

class mint
{
public:
  static ll MOD;
  ll x;

  mint() : x(0) {}

  mint(ll x) : x(x % MOD) {}

  mint &fix()
  {
    x = (x % MOD + MOD) % MOD;
    return *this;
  }

  mint operator-() const
  {
    return mint(0) - *this;
  }

  mint &operator+=(const mint &a)
  {
    if ((x += a.x) >= MOD)
    {
      x -= MOD;
    }
    return *this;
  }

  mint &operator-=(const mint &a)
  {
    if ((x += MOD - a.x) >= MOD)
    {
      x -= MOD;
    }
    return *this;
  }

  mint &operator*=(const mint &a)
  {
    (x *= a.x) %= MOD;
    return *this;
  }

  mint &operator/=(const mint &a)
  {
    return (*this *= power(MOD - 2));
  }

  mint operator+(const mint &a) const
  {
    return mint(*this) += a;
  }

  mint operator-(const mint &a) const
  {
    return mint(*this) -= a;
  }

  mint operator*(const mint &a) const
  {
    return mint(*this) *= a;
  }

  mint operator/(const mint &a) const
  {
    return mint(*this) /= a;
  }

  bool operator<(const mint &a) const
  {
    return x < a.x;
  }

  bool operator==(const mint &a) const
  {
    return x == a.x;
  }

  const mint power(ll N)
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
      mint half = power(N / 2);
      return half * half;
    }
  }
};

ll mint::MOD = 1e9 + 7;

istream &operator>>(istream &stream, mint &a)
{
  stream >> a.x;
  return stream;
}

ostream &operator<<(ostream &stream, const mint &a)
{
  stream << a.x;
  return stream;
}

mint inv[MAX_SIZE];
mint fact[MAX_SIZE];
mint factinv[MAX_SIZE];

void init()
{
  inv[1] = 1;
  for (int i = 2; i < MAX_SIZE; i++)
  {
    inv[i] = (-inv[mint::MOD % i]) * (mint::MOD / i);
  }
  fact[0] = factinv[0] = 1;
  for (int i = 1; i < MAX_SIZE; i++)
  {
    fact[i] = mint(i) * fact[i - 1];
    factinv[i] = inv[i] * factinv[i - 1];
  }
}

mint C(int n, int k)
{
  if (n >= 0 && k >= 0 && n - k >= 0)
  {
    return fact[n] * factinv[k] * factinv[n - k];
  }
  return 0;
}

long long gcd(long long x, long long y)
{
  return y ? gcd(y, x % y) : x;
}

int main()
{
  init();
}
