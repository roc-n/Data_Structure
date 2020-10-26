#include <iostream>
#include <string>
using namespace std;
typedef struct tests
{
    int a;
    int b;
    string name;
} Tests;
using namespace std;
Tests test()
{
    Tests test;
    test.a = 90;
    test.b = 100;
    test.name = "Hello!";
    return test;
}

int main(void)
{

    Tests b = test();
    cout << b.a << "  " << b.b << "  "
         << b.name << endl;
    return 0;
}