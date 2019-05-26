#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_SIZE = 1000010;
bool isprime[MAX_SIZE];
vector<int> prime_num;

void init()
{
  fill(isprime, isprime + MAX_SIZE, true);
  isprime[0] = isprime[1] = false;
  for (auto i = 2; i < MAX_SIZE; i++)
  {
    if (isprime[i])
    {
      prime_num.push_back(i);
      for (auto j = 2; i * j < MAX_SIZE; j++)
      {
        isprime[i * j] = false;
      }
    }
  }
}

bool is_prime(long long x)
{ // 2 \leq x \leq MAX_SIZE^2
  if (x < MAX_SIZE)
  {
    return isprime[x];
  }
  for (auto e : prime_num)
  {
    if (x % e == 0)
      return false;
  }
  return true;
}

vector<long long> make_factors(long long x)
{ // 2 \leq x \leq MAX_SIZE^2
  vector<long long> ans;
  auto it = prime_num.begin();
  while (it != prime_num.end())
  {
    if (x == 1)
    {
      break;
    }
    while (x % *it == 0)
    {
      ans.push_back(*it);
      x /= *it;
    }
    it++;
  }
  if (x != 1)
  {
    ans.push_back(x);
  }
  return ans;
}

int main()
{
  init();
  long long x;
  cin >> x;
  cout << (is_prime(x) ? "Prime" : "Not Prime") << endl;
}
