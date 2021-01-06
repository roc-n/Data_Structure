#include <iostream>
using namespace std;
int Hash(string str, string arr[]);
int main(void) {
  int index = 0;

  string arr[4] = {"abcd", "abdc", "cdba", "bbcd"};
  string strarr[10];
  for (int i = 0; i < 4; i++) {
    index = Hash(arr[i], strarr);
    arr[index] = arr[i];
  }
  for (int i = 0; i < 10; i++) {
    cout << i << ":" << strarr[i] << endl;
  }
  return 0;
}
// 哈希函数进行映射
int Hash(string str, string arr[]) {
  int hash = 0;
  for (int i = 0; i < str.length(); i++) {
    hash = (hash * 4 + str.at(i)) % 10;
  }
  return hash;
}