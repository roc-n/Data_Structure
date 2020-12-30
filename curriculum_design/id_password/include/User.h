#ifndef _USER_H_
#define _USER_H_
#include <string>
#include <vector>
using namespace std;
typedef struct item {
  int num;
  string password;
} Item, *ptrToItem;
class User {
public:
  int user_num;
  void Read_To_Arr();
  
};
#endif