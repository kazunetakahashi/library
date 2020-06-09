#include "../SegTree.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H&lang=ja"

int main()
{
  int N;
  cin >> N;
  auto tree{RMQ_RAQ<ll>(N)};
  int Q;
  cin >> Q;
  for (auto q{0}; q < Q; ++q)
  {
    int t;
    cin >> t;
    if (t == 0)
    {
      int s, t;
      ll x;
      cin >> s >> t >> x;
      tree.update(s, t + 1, make_tuple(x, true));
    }
    else
    {
      int s, t;
      cin >> s >> t;
      cout << tree.query(s, t + 1) << endl;
    }
  }
}
