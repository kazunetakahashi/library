---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: Tools/Compressor.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8625e1de7be14c39b1d14dc03d822497">Tools</a>
* <a href="{{ site.github.repository_url }}/blob/master/Tools/Compressor.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-02 17:08:46+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Tools/Compressor.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

