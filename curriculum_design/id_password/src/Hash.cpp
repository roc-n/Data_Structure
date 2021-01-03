#include "../include/Hash.h"

ptrToItem &Hash::operator[](string &pwd) {
  Calculate(pwd, first);
  return arr[this->index];
}

void Hash::Store(Item &item) {
  Calculate(item.password, first);
  //   发生冲突则再哈希
  if (arr[this->index] != nullptr) {
    //   密码若与原址存储的相同则不做处理
    if (arr[this->index]->password != item.password) {
      first = false;
      do {
        Calculate(item.password, first);
      } while (arr[this->index] != nullptr);
      first = true;
    }
  }
  arr[this->index] = new Item;
  arr[this->index]->password = item.password;
  arr[this->index]->num = item.num;
}

void Hash::Calculate(string &pwd, bool first) {
  this->index = 0;
  if (first) {
    for (ull i = 1; i < pwd.length(); i++) {
      this->index = (this->index * p1 + (int)pwd.at(i)) % mod;
    }
  } else {
    for (ull j = 1; j < pwd.length(); j++) {
      this->index = (this->index * p2 + (int)pwd.at(j)) % mod;
    }
  }
}

Hash::Hash() {
  arr = (ptrToItem *)new ptrToItem[mod];
  for (ull i = 0; i < mod; i++) {
    arr[i] = nullptr;
  }
  first = true;
}

Hash::~Hash() {
  for (ull i = 0; i < mod; i++) {
    if (arr[i] != nullptr) {
      delete arr[i];
    }
  }
  delete[] arr;
}