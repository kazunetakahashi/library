#include <vector>
#include <string>
using namespace std;

template <typename T>
class RollingHash
{
  string S;
  static T B;
  vector<T> H;

public:
  RollingHash(string s, int t = -1) : S{s}
  {
    if (t == -1)
    {
      t = s.size();
    }
    assert(1 <= t && t <= static_cast<int>(s.size()));
    H = make_init_hash(t);
  }

  RollingHash(string s, size_t t) : RollingHash{s, static_cast<int>(t)} {}

  size_t size()
  {
    return S.size() + 1u - H.size();
  }

  const T operator[](size_t t) const { return H[t]; }

private:
  T Sm(size_t k) { return static_cast<T>(S[k]); }
  vector<T> make_init_hash(int);
};

template <typename T>
T RollingHash<T>::B = 1234567;

template <typename T>
vector<T> RollingHash<T>::make_init_hash(int t)
{
  vector<T> res(S.size() + 1 - t);
  T now = 0;
  const T pb = B.power(t);
  for (auto i = 0; i < t; i++)
  {
    now = now * B + Sm(i);
  }
  res[0] = now;
  for (auto i = 0u; i < res.size() - 1; i++)
  {
    res[i + 1] = res[i] * B - Sm(i) * pb + Sm(i + t);
  }
  return res;
}
