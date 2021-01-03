#include "../include/User.h"
#include <iostream>
using namespace std;
int main(void) {
  User user;
  user.Generate_Passsword_File();
  user.SortPassword();
  user.ReadToList();
  user.ReadToTree();
  user.Generate_Userid_File();
  user.BinarySearch();
  user.ReadToHash();
  return 0;
}