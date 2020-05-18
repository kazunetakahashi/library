#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
using ll = long long;

// ----- Sieve -----

class Sieve
{
  static constexpr ll MAX_SIZE{1000010LL};
  ll N;
  vector<ll> f;
  vector<ll> prime_nums;

public:
  Sieve(ll N = MAX_SIZE) : N{N}, f(N, 0), prime_nums{}
  {
    f[0] = f[1] = -1;
    for (auto i = 2; i < N; i++)
    {
      if (f[i])
      {
        continue;
      }
      prime_nums.push_back(i);
      f[i] = i;
      for (auto j = 2 * i; j < N; j += i)
      {
        if (!f[j])
        {
          f[j] = i;
        }
      }
    }
  }

  bool is_prime(ll x) const
  { // 2 \leq x \leq MAX_SIZE^2
    if (x < N)
    {
      return f[x] == x;
    }
    for (auto e : prime_nums)
    {
      if (x % e == 0)
      {
        return false;
      }
    }
    return true;
  }

  vector<ll> const &primes() const
  {
    return prime_nums;
  }

  vector<ll> factor_list(ll x) const
  {
    if (x < 2)
    {
      return {};
    }
    vector<ll> res;
    auto it{prime_nums.begin()};
    if (x < N)
    {
      while (x != 1)
      {
        res.push_back(f[x]);
        x /= f[x];
      }
    }
    else
    {
      while (x != 1 && it != prime_nums.end())
      {
        if (x % *it == 0)
        {
          res.push_back(*it);
          x /= *it;
        }
        else
        {
          ++it;
        }
      }
      if (x != 1)
      {
        res.push_back(x);
      }
    }
    return res;
  }

  vector<tuple<ll, ll>> factor(ll x) const
  {
    if (x < 2)
    {
      return {};
    }
    auto factors{factor_list(x)};
    vector<tuple<ll, ll>> res{make_tuple(factors[0], 0)};
    for (auto x : factors)
    {
      if (x == get<0>(res.back()))
      {
        get<1>(res.back())++;
      }
      else
      {
        res.emplace_back(x, 1);
      }
    }
    return res;
  }
};
