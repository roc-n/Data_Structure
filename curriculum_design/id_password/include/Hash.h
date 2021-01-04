#ifndef _HASH_
/*
  哈希函数的声明,以类封装,采取开放寻址法中的再哈希策略,即发生冲突时采取不同的参数再次计算哈希值,直到遇到未被填充的槽位
*/

#define _HASH_
#include "User.h"
#include <string>
#define ull unsigned long long
using std::string;

class Hash {
private:
  // 哈希函数计算的参数
  ull p1 = 786433, p2 = 393241;
  ull mod = 1000000007;
  // 决定哈希函数以哪个质数进行计算
  bool first;
  // 记录下标值
  int index;
  // 指针数组,地址为哈希函数值
  ptrToItem *arr;

public:
  // 重载运算符,以密码作为下标返回出现次数
  ptrToItem &operator[](string &pwd);
  // 哈希函数的计算
  void Calculate(string &pwd, bool first);
  // 键-值对应存储
  void Store(Item &item);
  Hash();
  ~Hash();
};
#endif