#include "User.h"
#include <string>
using std::string;
// 哈希元组
typedef struct HashTuple {
  int value1;
  int value2;
} * tuples;

class Hash {
private:
  int value1;
  int value2;
  tuples *tuple;

  int index;

public:
  int &operator[](string &pwd);
  Hash(int n);
  ~Hash();
  tuples DoubleHash(string &pwd);
  void Check();
};

inline int &Hash::operator[](string &pwd) {
  this->tuple[index] = DoubleHash(pwd);
  return index;
}

inline tuples Hash::DoubleHash(string &pwd) {
  tuples tuple = new HashTuple;
  int p1 = 786433, mod1 = 200;
  int p2 = 393241, mod2 = 234;
  for (int i = 1; i < pwd.length(); i++) {
    tuple->value1 = (tuple->value1 * p1 + (int)pwd.at(i)) % mod1;
  }
  for (int j = 1; j < pwd.length(); j++) {
    tuple->value2 = (tuple->value2 * p2 + (int)pwd.at(j)) % mod2;
  }
  return tuple;
}

inline Hash::Hash(int n) {
  tuple = (tuples *)new tuples[n];
  index = -1;
}

inline Hash::~Hash() { delete[] tuple; }