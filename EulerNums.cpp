#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// ----- EulerNums -----

class EulerNums
{
  static constexpr ll MAX_SIZE{1000010LL};
  ll N;
  vector<ll> table;

public:
  EulerNums(ll N = MAX_SIZE) : N{N}
  {
    table.resize(N);
    for (auto i = 0; i < N; i++)
    {
      table[i] = i;
    }
    for (auto i = 2; i < N; i++)
    {
      if (table[i] == i)
      {
        for (auto j = i; j < N; j += i)
        {
          table[j] = table[j] / i * (i - 1);
        }
      }
    }
  }

  ll euler(ll n)
  {
    if (n < N)
    {
      return table[N];
    }
    else
    {
      ll res{n};
      for (auto i = 2LL; i * i <= n; i++)
      {
        if (n % i == 0)
        {
          res = res / i * (i - 1);
        }
        for (; n % i == 0; n /= i)
        {
        }
      }
      if (n != 1)
      {
        res = res / n * (n - 1);
      }
      return res;
    }
  }
};
