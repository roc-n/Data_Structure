#include "../include/User.h"
#include <iostream>
using namespace std;
int main(void) {
  User user;
  cout << "正在生成密码与出现次数的映射文件:" << endl;
  user.Generate_Passsword_File();
  cout << "正在生成依据用户id进行排序的文件:" << endl;
  user.Generate_Userid_File();
  cout << "应用排序函数依据密码出现次数进行排序:" << endl;
  user.SortPassword();
  cout << "将数据读入链表并进行搜索:" << endl;
  user.ReadToListAndSearch();
  cout << "将数据读入树中并进行搜索:" << endl;
  user.ReadToTreeAndSearch();
  cout << "将排好序的用户id读入数组,应用二分查找进行搜索:" << endl;
  user.BinarySearch();
  cout << "将数据读入哈希表并进行搜索:" << endl;
  user.ReadToHash();
  return 0;
}