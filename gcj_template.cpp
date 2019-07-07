#include <iostream>
using namespace std;

void init()
{
}

// 変数を書く

void input()
{
  // cin >> ;
}

void output()
{
  cout << endl;
}

int main()
{
  init();
  int T;
  cin >> T;
  for (auto t = 1; t <= T; t++)
  {
    cout << "Case #" << t << ": ";
    input();
    output();
  }
}
