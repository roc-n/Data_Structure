<<<<<<< HEAD
#include <iostream>
using namespace std;
void Swap(const char *&a, const char *&b) {
  const char *tmp = a;
  a = b;
  b = tmp;
}
void QuickSort(char *arr[], int n) {}

int main(void) {
  const char *arr[20] = {"ww", "as", "3w2"};
  Swap(arr[0], arr[1]);
  cout << arr[0] << " " << arr[1] << endl;
  return 0;
=======
#include <iostream>
using namespace std;
void Swap(const char *&a, const char *&b) {
  const char *tmp = a;
  a = b;
  b = tmp;
}
void QuickSort(char *arr[], int n) {}

int main(void) {
  const char *arr[20] = {"ww", "as", "3w2"};
  Swap(arr[0], arr[1]);
  cout << arr[0] << " " << arr[1] << endl;
  return 0;
>>>>>>> 558a2997b1b1b27da35cc1c92573a0f223ec6bc5
}