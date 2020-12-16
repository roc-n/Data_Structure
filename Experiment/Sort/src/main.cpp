#include "../include/Sort.h"
// 将C风格字符串转化为C++String类进行存储
void Transform(const char *origin_arr[], ptrToItem arr[], int n) {
  ptrToItem item_arr;
  for (int i = 0; i < n; i++) {
    item_arr = new item;
    item_arr->str = origin_arr[i];
    arr[i] = item_arr;
  }
}

void Display(const ptrToItem arr[], int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i]->str << "	";
    if ((i + 1) % 5 == 0) {
      cout << endl;
    }
  }
}

int main(int argc, char *argv[]) {
  // 以三国人物名称进行测试
  const char *origin_arr[20] = {"guanyu", "zhangfei", "guojia", "xiahoudun",
                                "sunce",  "luxun",    "machao", "sunquan",
                                "caocao", "liubei"};
  int n = 10;
  ptrToItem arr[n];
  Transform(origin_arr, arr, n);

  // QuickSort(arr, 0, n - 1);
  // MergeSort(arr, n);
  HeapSort(arr, n);
  Display(arr, n);
  for (int i = 0; i < n; i++) {
    delete arr[i];
  }

  return 0;
}