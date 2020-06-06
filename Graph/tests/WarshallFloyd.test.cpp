#include "../WarshallFloyd.cpp"

// ----- main -----

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"

template <typename T>
constexpr T Infty()
{
  return numeric_limits<T>::max();
}

int main()
{
  int N, M;
  cin >> N >> M;
  vector<vector<ll>> D(N, vector<ll>(N, Infty<ll>()));
  for (auto i{0}; i < M; ++i)
  {
    int A, B;
    ll C;
    cin >> A >> B >> C;
    D[A][B] = C;
  }
  for (auto i{0}; i < N; ++i)
  {
    D[i][i] = 0;
  }
  WarshallFloyd(D);
  for (auto i{0}; i < N; ++i)
  {
    if (D[i][i] < 0)
    {
      cout << "NEGATIVE CYCLE" << endl;
      return 0;
    }
  }
  for (auto i{0}; i < N; ++i)
  {
    for (auto j{0}; j < N; ++j)
    {
      cout << (D[i][j] == Infty<ll>() ? "INF" : to_string(D[i][j]));
      if (j < N - 1)
      {
        cout << " ";
      }
      else
      {
        cout << endl;
      }
    }
  }
}
