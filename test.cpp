#include <cstring>
#include <iostream>
#include <string>
using namespace std;
void add(int a, int b = 1);
typedef struct tests {
  int a;
  int b;
  string name;
} Tests;

Tests test() {
  Tests test;
  test.a = 90;
  test.b = 100;
  test.name = "Hello!";
  return test;
}
typedef void (*pf)(int, int);
int main(void) {

  Tests b = test();
  cout << b.a << "  " << b.b << "  " << b.name << endl;

  string a = "Helloszz!";
  const char *str = a.c_str();
  cout << str << sizeof(str) << endl;
  char ss[] = "Hello!";
  cout << sizeof(ss) << endl;
  cout << strlen(ss) << endl;

  cout << a[0] << endl;
  string::iterator i = a.begin();
  // char *= a.begin();
  for (i = a.begin(); i != a.end(); ++i) {
    cout << *i;
  }

  string q;
  q += 's';
  cout << q << endl;

  char ch1 = 'e';
  string s1;
  s1.push_back(ch1);
  cout << a.length() << a.substr(1, 5) << endl;
  char s = a[0];
  cout << s << endl;

  // ch可以和string对象直接串接
  string test = "as";
  char ch = 'a';
  test = test + ch;
  cout << test << endl;
  pf pointerToFunction = &add;
  pointerToFunction(100);
  return 0;
  // **************************
}

void add(int a, int b) { cout << a + b << endl; }
