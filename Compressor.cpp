#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
using ll = long long;

// ----- Compressor -----
// referring to ymatsux-san's code:
// https://atcoder.jp/contests/abc168/submissions/13337691

template <typename T = ll>
class Compressor
{
  vector<T> raw;
  map<T, int> index;

public:
  Compressor() {}

  template <typename Container>
  Compressor(Container const &V) { append(V); }

  template <typename Iter>
  Compressor(Iter first, Iter last) { append(first, last); }

  template <typename Container>
  void append(Container const &V) { append(V.begin(), V.end()); }

  template <typename Iter>
  void append(Iter first, Iter last)
  {
    set<T> S(first, last);
    raw = vector<T>(S.begin(), S.end());
    sort(raw.begin(), raw.end());
    for (auto i = size_t{0}; i < raw.size(); ++i)
    {
      index[raw[i]] = i;
    }
  }

  T to_raw(int i) { return raw[i]; }
  int to_index(T t) { return index[t]; }
};

// https://atcoder.jp/contests/abc113/tasks/abc113_c

int main()
{
  int N, M;
  cin >> N >> M;
  using Pref = tuple<int, int>;
  vector<Pref> P(M);
  for (auto i = 0; i < M; ++i)
  {
    cin >> get<0>(P[i]) >> get<1>(P[i]);
  }
  vector<vector<int>> V(N);
  for (auto i = 0; i < M; ++i)
  {
    V[get<0>(P[i]) - 1].push_back(get<1>(P[i]));
  }
  vector<Compressor<int>> C(N);
  for (auto i = 0; i < N; ++i)
  {
    C[i].append(V[i]);
  }
  for (auto i = 0; i < M; ++i)
  {
    int pref, code;
    tie(pref, code) = P[i];
    cout << setw(6) << setfill('0') << pref
         << setw(6) << setfill('0') << C[pref - 1].to_index(code) + 1 << endl;
  }
}
