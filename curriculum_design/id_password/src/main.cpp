#include "../include/Sort.h"
#include "../include/User.h"
#include <iostream>
using namespace std;
void Display(ptrToItem arr[], int n);
void DisPose(ptrToItem arr[], int n);
int main(int argc, char *argv[]) {
  int n = 10;
  ptrToItem arr[n];
  ptrToItem items = new item[n];
  for (int i = 0; i < 10; i++) {
    items[i].num = i;
    arr[i] = &items[i];
  }
  ptrToItem tmp = arr[8];
  arr[8] = arr[3];
  arr[3] = tmp;
  // Display(arr, n);
  // QuickSort(arr, 0, 9);
  // Inverse(arr, n);
  // Display(arr, n);
  // HeapSort(arr, n);
  // BubbleSort(arr, n);
  // ChooseSort(arr, n);
  // InsertSort(arr, n);
  // MergeSort(arr, n);
  // ShellSort(arr, n);
  // RadixSort(arr, n);
  delete[] items;
  int arrB[1200000];
  arrB[0] = 100;
  cout<<arrB[0]<<endl;
  return 0;
}
void Display(ptrToItem arr[], int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i]->num << endl;
  }
}

void DisPose(ptrToItem arr[], int n) {
  for (int i = 0; i < n; i++) {
    delete arr[i];
  }
}