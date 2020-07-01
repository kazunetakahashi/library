#include "../LIS.cpp"

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D&lang=jp"

int main()
{
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto i{0}; i < n; ++i)
  {
    cin >> a[i];
  }
  LIS<int> lis(n);
  for (auto i{0}; i < n - 1; ++i)
  {
    lis.query(a[i]);
  }
  cout << lis.query(a[n - 1]) << endl;
}
