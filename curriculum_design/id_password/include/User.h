#ifndef _USER_
#define _USER_
#include <string>
using namespace std;
// 定义存储信息的结构
typedef struct item {
  int num;
  string password;
} Item, *ptrToItem;

// 将程序中要实现的功能包装成相关函数，以类封装
class User {
public:
  // User();
  // ~User();
  // int user_num;
  void Generate_Passsword_File();
  void Generate_Userid_File();
  void SortPassword();
  void ReadToList();
  void ReadToTree();
  void BinarySearch();
  // void Hash(string str, HashTuple &tuple);
};
ptrToItem BinarySearch(ptrToItem arr[], int size, int target);
#endif