#include "../SuffixArray.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D&lang=ja"

int main()
{
  string S;
  int Q;
  cin >> S >> Q;
  vector<string> T(Q);
  for (auto i = 0; i < Q; i++)
  {
    cin >> T[i];
  }
  SuffixArray<string> sa(S);
  for (auto i = 0; i < Q; i++)
  {
    cout << (sa.contain(T[i]) ? 1 : 0) << endl;
  }
}
