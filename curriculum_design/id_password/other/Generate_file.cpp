#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

char getDigit() { return static_cast<char>('0' + rand() % ('9' - '0' + 1)); }
char getLower() { return static_cast<char>('a' + rand() % ('z' - 'a' + 1)); }
char getUpper() { return static_cast<char>('A' + rand() % ('Z' - 'A' + 1)); }
int getlength() { return rand() % 14 + 6; }

int main() {
  int id = 1;
  ofstream output;
  output.open("user.txt");
  srand(time(0));
  char ch;          //保存随机生成的字符
  int num;          //决定随机生成字符的类型
  int npwd;         //输出密码的个数
  vector<char> str; //保存随机生成的字符串
  cout << "Enter the number of passwords: ";
  cin >> npwd;
  for (int j = 0; j < npwd; j++) {
    for (int i = 0; i < 19; i++) //默认生成十九位字符串密码
    {
      num = rand() % 3;
      if (num == 0)
        ch = getDigit();
      else if (num == 1)
        ch = getLower();
      else
        ch = getUpper();
      str.push_back(ch);
    }
    str.resize(getlength()); //随机密码长度处于6到19之间
    vector<char>::iterator p1;
    output << id++ << " ";
    for (p1 = str.begin(); p1 != str.end(); p1++) {
      output << *p1;
    }
    output << endl;
    str.clear();
  }
  cout << "Done" << endl;
  output.close();
  return 0;
}
