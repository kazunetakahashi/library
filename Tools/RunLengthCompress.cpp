#include <tuple>
#include <vector>
using namespace std;

// ----- RunLengthCompress -----

template <typename T>
auto RunLengthCompress(T const &S) -> vector<tuple<remove_const_t<remove_reference_t<decltype(S[0])>>, int>>
{
  using U = remove_const_t<remove_reference_t<decltype(S[0])>>;
  vector<tuple<U, int>> res;
  U c{S[0]};
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
