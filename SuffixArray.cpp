#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// ----- SuffixArray -----

class SuffixArray
{
  int N, K;
  string S;
  vector<int> sa;

public:
  SuffixArray(string S) : N{static_cast<int>(S.size())}, K{1}, S{S}, sa(N + 1)
  {
    // initialize for 1 char
    for (auto i = 0; i <= N; i++)
    {
      sa[i] = i;
    }
    vector<int> rank(N + 1);
    for (auto i = 0; i < N; i++)
    {
      rank[i] = static_cast<int>(S[i]);
    }
    rank[N] = -1;
    // lambda for comparing
    auto compare_sa = [&](auto i, auto j) {
      if (rank[i] != rank[j])
      {
        return rank[i] < rank[j];
      }
      else
      {
        int ri{i + K <= N ? rank[i + K] : -1};
        int rj{j + K <= N ? rank[j + K] : -1};
        return ri < rj;
      }
    };
    // construct sa with rank
    vector<int> tmp(N + 1);
    for (; K <= N; K *= 2)
    {
      sort(sa.begin(), sa.end(), compare_sa);
      tmp[sa[0]] = 0;
      for (auto i = 1; i <= N; i++)
      {
        tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
      }
      swap(rank, tmp);
    }
  }

  int operator[](int i) const
  {
    return sa[i];
  }

  bool contain(string const &T) const
  {
    int b{lower_bound(T)};
    return b <= N && S.compare(sa[b], T.size(), T) == 0;
  }

  int count(string const &T) const
  {
    int lb{lower_bound(T)};
    int ub{upper_bound(T)};
    if (lb > ub)
    {
      return 0;
    }
    return ub - lb + 1;
  }

private:
  template <typename T>
  void binary_search(int &a, int &b, T cmp) const
  {
    while (abs(a - b) > 1)
    {
      int c{(a + b) / 2};
      if (cmp(c))
      {
        a = c;
      }
      else
      {
        b = c;
      }
    }
  }

  int lower_bound(string const &T) const
  {
    int a{-1}, b{N + 1};
    auto cmp = [&](auto c) {
      return S.compare(sa[c], T.size(), T) < 0;
    };
    binary_search(a, b, cmp);
    return b;
  }

  int upper_bound(string const &T) const
  {
    int a{-1}, b{N + 1};
    auto cmp = [&](auto c) {
      return S.compare(sa[c], T.size(), T) <= 0;
    };
    binary_search(a, b, cmp);
    return a;
  }
};

// ----- main() -----

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D&lang=ja

void solve()
{
  string S;
  int Q;
  cin >> S >> Q;
  vector<string> T(Q);
  for (auto i = 0; i < Q; i++)
  {
    cin >> T[i];
  }
  SuffixArray sa(S);
  for (auto i = 0; i < Q; i++)
  {
    cout << (sa.contain(T[i]) ? 1 : 0) << endl;
  }
}

int main()
{
  string S, T;
  cin >> S >> T;
  SuffixArray sa(S);
  cout << sa.count(T) << endl;
}
