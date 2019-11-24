#include <vector>
#include <tuple>
#include <cassert>
using namespace std;
using ll = long long;

// for C++14
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }

// ----- LinearMod -----

class LinearMod
{
  vector<ll> A, B, M;

public:
  LinearMod() {}

  void add(ll a, ll b, ll m)
  {
    A.push_back(a);
    B.push_back(b);
    M.push_back(m);
  }

  tuple<ll, ll> get()
  {
    assert(A.size() == B.size() && B.size() == M.size());
    ll x{0}, m{1};
    for (auto i = 0; i < A.size(); i++)
    {
      ll a{A[i] * m};
      ll b{B[i] - A[i] * x};
      ll d{gcd(M[i], a)};
      if (b % d != 0)
      {
        return make_tuple(0, -1);
      }
      ll t{b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d)};
      x = x + m * t;
      m *= M[i] / d;
    }
    return make_tuple(x % m, m);
  }

private:
  static ll extra_gcd(ll a, ll b, ll &x, ll &y)
  {
    ll d{a};
    if (b != 0)
    {
      d = extra_gcd(b, a % b, y, x);
      y -= (a / b) * x;
    }
    else
    {
      x = 1;
      y = 0;
    }
    return d;
  }

  static ll mod_inverse(ll a, ll m)
  {
    ll x, y;
    extra_gcd(a, m, x, y);
    return (m + x % m) % m;
  }
};
