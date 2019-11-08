#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

class PrimeNums
{
  static constexpr ll MAX_SIZE{1000010LL};
  ll N;
  vector<bool> isprime;
  vector<int> prime_nums;

public:
  PrimeNums(ll N = MAX_SIZE) : N{N}
  {
    isprime.resize(N, true);
    isprime[0] = isprime[1] = false;
    for (auto i = 2; i < N; i++)
    {
      if (isprime[i])
      {
        prime_nums.push_back(i);
        for (auto j = 2 * i; j < N; j += i)
        {
          isprime[j] = false;
        }
      }
    }
  }

  bool is_prime(long long x)
  { // 2 \leq x \leq MAX_SIZE^2
    if (x < N)
    {
      return isprime[x];
    }
    for (auto e : prime_nums)
    {
      if (x % e == 0)
        return false;
    }
    return true;
  }

  vector<int> const &primes() const
  {
    return prime_nums;
  }
};

int main()
{
  PrimeNums P{};
  ll x;
  cin >> x;
  cout << (P.is_prime(x) ? "Prime" : "Not Prime") << endl;
}
