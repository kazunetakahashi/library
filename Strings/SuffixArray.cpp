#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// ----- SuffixArray -----

template <typename Type = string>
class SuffixArray
{
public:
  // Sparse Table from drken-san
  // http://drken1215.hatenablog.com/entry/2019/09/16/014600
  template <typename T = int>
  class SparseTable
  {
    vector<vector<T>> dat;
    vector<int> height;

  public:
    SparseTable() {}
    SparseTable(vector<T> const &V)
    {
      int N{static_cast<int>(V.size())}, h{0};
      while ((1 << h) < N)
      {
        ++h;
      }
      dat.assign(h, vector<T>(1 << h));
      height.assign(N + 1, 0);
      for (int i = 2; i <= N; i++)
      {
        height[i] = height[i >> 1] + 1;
      }
      for (int i = 0; i < N; ++i)
      {
        dat[0][i] = V[i];
      }
      for (int i = 1; i < h; ++i)
      {
        for (int j = 0; j < N; ++j)
        {
          dat[i][j] = min(dat[i - 1][j], dat[i - 1][min(j + (1 << (i - 1)), N - 1)]);
        }
      }
    }

    T get(int a, int b) const
    {
      return min(dat[height[b - a]][a], dat[height[b - a]][b - (1 << height[b - a])]);
    }
  };

private:
  int N, K;
  Type S;
  vector<int> rank, sa, lcp;
  SparseTable<int> st;

public:
  SuffixArray() {}
  SuffixArray(Type const &S) : N{static_cast<int>(S.size())}, K{1}, S{S}, rank(N + 1), sa(N + 1), lcp(N)
  {
    // initialize for 1 char
    for (auto i = 0; i <= N; i++)
    {
      sa[i] = i;
    }
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
    // construct lcp with sa and rank
    for (auto i = 0; i <= N; i++)
    {
      rank[sa[i]] = i;
    }
    int h{0};
    lcp[0] = 0;
    for (auto i = 0; i < N; i++)
    {
      int j{sa[rank[i] - 1]};
      if (h > 0)
      {
        --h;
      }
      for (; j + h < N && i + h < N; ++h)
      {
        if (S[j + h] != S[i + h])
        {
          break;
        }
      }
      lcp[rank[i] - 1] = h;
    }
    st = SparseTable<int>(lcp);
  }

  int operator[](int i) const
  {
    return sa[i];
  }

  vector<int> const &LCP() const
  {
    return lcp;
  }

  int LCP(int a, int b) const
  {
    return st.get(min(rank[a], rank[b]), max(rank[a], rank[b]));
  }

  bool contain(Type const &T) const
  {
    int b{lower_bound(T)};
    return b <= N && S.compare(sa[b], T.size(), T) == 0;
  }

  int count(Type const &T) const
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

  int lower_bound(Type const &T) const
  {
    int a{-1}, b{N + 1};
    auto cmp = [&](auto c) {
      return S.compare(sa[c], T.size(), T) < 0;
    };
    binary_search(a, b, cmp);
    return b;
  }

  int upper_bound(Type const &T) const
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

void solve_contain()
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

void solve_count()
{
  string S, T;
  cin >> S >> T;
  SuffixArray<string> sa(S);
  cout << sa.count(T) << endl;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0528

template <typename T>
void ch_max(T &left, T right)
{
  if (left < right)
  {
    left = right;
  }
}

int common_sub_string(string const &S, string const &T)
{
  string U{S + "$" + T};
  int L{static_cast<int>(S.size())};
  SuffixArray<string> sa{U};
  int ans{0};
  for (auto i = 0; i < static_cast<int>(U.size()); i++)
  {
    if ((sa[i] < L) ^ (sa[i + 1] < L))
    {
      ch_max(ans, sa.LCP()[i]);
    }
  }
  return ans;
}

void solve_common_sub_string()
{
  string S, T;
  while (cin >> S >> T)
  {
    cout << common_sub_string(S, T) << endl;
  }
}
