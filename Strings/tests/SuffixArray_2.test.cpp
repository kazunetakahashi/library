#include "../SuffixArray.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0528"

int main()
{
  string S, T;
  while (cin >> S >> T)
  {
    cout << common_sub_string(S, T) << endl;
  }
}
