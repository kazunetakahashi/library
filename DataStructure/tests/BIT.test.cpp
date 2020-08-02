#include "../BIT.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=ja"

int main()
{
  int N;
  cin >> N;
  BIT<long long> tree{N};
  int Q;
  cin >> Q;
  for (auto q{0}; q < Q; ++q)
  {
    int t;
    cin >> t;
    if (t == 0)
    {
      int k, x;
      cin >> k >> x;
      --k;
      tree.add(k, x);
    }
    else
    {
      int s, t;
      cin >> s >> t;
      --s;
      --t;
      cout << tree.sum(s, t + 1) << endl;
    }
  }
}
