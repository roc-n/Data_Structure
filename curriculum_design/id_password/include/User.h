/*
  主程序的类及存储数据的结构声明
*/
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
  int user_num;
  // 生成密码与出现次数的映射文件
  void Generate_Passsword_File();
  // 生成用户id文件
  void Generate_Userid_File();
  // 对出现次数进行排序
  void SortPassword();
  // 读入到链表并搜索
  void ReadToListAndSearch();
  // 读入到avl树并搜索
  void ReadToTreeAndSearch();
  // 二分查找
  void BinarySearch();
  // 读入到哈希表中并搜索
  void ReadToHash();
};
// 二分查找函数
ptrToItem BinarySearch(ptrToItem arr[], int size, int target);
#endif