#include <tuple>
#include <vector>
using namespace std;

// ----- RunLengthCompress -----

template <typename T>
auto RunLengthCompress(T const &S) -> vector<tuple<decltype(S[0]), int>>
{
  vector<tuple<decltype(S[0]), int>> res;
  auto c{S[0]};
  int x{0};
  for (auto e : S)
  {
    if (c == e)
    {
      ++x;
    }
    else
    {
      res.emplace_back(c, x);
      c = e;
      x = 1;
    }
  }
  res.emplace_back(c, x);
  return res;
}
