#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"

/*
  add(s,t,x): add x to a_i for i \in [s, t).
  get(i): output the value of a_i.
*/

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// ----- RangeAddQuery -----

template <typename T = ll>
class RangeAddQuery
{ // index starts at 0.
  int N;
  vector<T> data;

public:
  RangeAddQuery(int N) : N{N}, data(N + 1, T{0}) {}

  T get(int i)
  {
    return _sum(i + 1);
  }

  void add(int a, int b, T x)
  { // [a, b)
    _add(a + 1, x);
    _add(b + 1, -x);
  }

private:
  T _sum(int i)
  { // [1, i]
    T s{0};
    while (i > 0)
    {
      s += data[i];
      i -= i & -i;
    }
    return s;
  }

  void _add(int i, ll x)
  {
    while (i <= N)
    {
      data[i] += x;
      i += i & -i;
    }
  }
};

// ----- main -----

int main()
{
  int N, Q;
  cin >> N >> Q;
  RangeAddQuery<ll> RAQ(N);
  for (auto i = 0; i < Q; ++i)
  {
    int c;
    cin >> c;
    if (c == 0)
    {
      int s, t;
      ll x;
      cin >> s >> t >> x;
      --s;
      --t;
      RAQ.add(s, t + 1, x);
    }
    else
    {
      int i;
      cin >> i;
      --i;
      cout << RAQ.get(i) << endl;
    }
  }
}
