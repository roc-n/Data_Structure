#include <ctime>
#include <iostream>

using namespace std;
// 定义存储数据的结构
typedef struct item {
  string str;
} Item, *ptrToItem;

// 归并排序
void MergeSort(ptrToItem arr[], int n);
// 快速排序
void QuickSort(ptrToItem arr[], int l_pos, int r_pos);
// 堆排序
void HeapSort(ptrToItem arr[], int n);