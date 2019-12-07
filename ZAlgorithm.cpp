#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ----- ZAlgorithm -----
// from drken-san: http://drken1215.hatenablog.com/entry/2019/09/16/014600

class ZAlgorithm
{
  int N;
  string S;
  vector<int> V;

public:
  ZAlgorithm() {}
  ZAlgorithm(string const &S) : N{static_cast<int>(S.size())}, S{S}, V(N)
  {
    V[0] = N;
    int i{1}, j{0};
    while (i < N)
    {
      while (i + j < N && S[j] == S[i + j])
      {
        ++j;
      }
      V[i] = j;
      if (j == 0)
      {
        ++i;
        continue;
      }
      int k{1};
      while (i + k < N && k + V[k] < j)
      {
        V[i + k] = V[k];
        ++k;
      }
      i += k;
      j -= k;
    }
  }

  int operator[](int i) const
  {
    return V[i];
  }
};

// https://atcoder.jp/contests/abc141/tasks/abc141_e

int main()
{
  int N;
  string S;
  cin >> N >> S;
  int ans{0};
  for (int i = 0; i < N; ++i)
  {
    string T{S.substr(i)};
    ZAlgorithm Z(T);
    for (int j = 0; j < static_cast<int>(T.size()); ++j)
    {
      ans = max(ans, min(Z[j], j));
    }
  }
  cout << ans << endl;
}
