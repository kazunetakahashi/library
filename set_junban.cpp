#include <iostream>
using namespace std;

int MAX_SIZE;

void junban(int USE_SIZE)
{ // USE_SIZE > 0
  int comb = (1 << USE_SIZE) - 1;
  while (comb < (1 << MAX_SIZE))
  {
    // ここで作業する
    for (auto i = 0; i < MAX_SIZE; i++)
    {
      if (((comb >> i) & 1) == 1)
      {
        cout << i << " ";
      }
    }
    cout << endl;
    // 以下処理。
    int tmp_x = comb & (-comb);
    int tmp_y = comb + tmp_x;
    int tmp_z = comb & (~(tmp_y));
    comb = (((tmp_z / tmp_x) >> 1) | tmp_y);
  }
}

int main()
{
  cout << "MAX_SIZE ? " << endl;
  cin >> MAX_SIZE;
  for (auto i = 1; i <= MAX_SIZE; i++)
  {
    cout << "SIZE = " << i << " : " << endl;
    junban(i);
  }
}
