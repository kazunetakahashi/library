#include "../KMP.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

int main()
{
  string t, p;
  cin >> t >> p;
  MP<string> mp{p};
  for (auto e : mp.place(t))
  {
    cout << e << endl;
  }
}
