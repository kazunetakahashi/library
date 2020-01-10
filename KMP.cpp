#include <vector>
#include <string>
using namespace std;

// ----- MP algorithm -----

template <typename Type = string>
class MP
{
  int N;
  Type S;
  vector<int> A;

public:
  MP() {}
  MP(Type const &S) : N(S.size()), S{S}, A(N + 1, -1)
  {
    int j{-1};
    for (auto i = 0; i < N; i++)
    {
      while (j != -1 && S[j] != S[i])
      {
        j = A[j];
      }
      ++j;
      A[i + 1] = j;
    }
  }

  int operator[](int i) { return A[i]; }

  vector<int> find_all(Type const &T)
  {
    vector<int> res;
    int j{0};
    for (auto i = 0; i < static_cast<int>(T.size()); i++)
    {
      while (j != -1 && S[j] != T[i])
      {
        j = A[j];
      }
      ++j;
      if (j == N)
      {
        res.push_back(i - j + 1);
        j = A[j];
      }
    }
    return res;
  }
};
