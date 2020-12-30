<<<<<<< HEAD
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
=======
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
>>>>>>> 558a2997b1b1b27da35cc1c92573a0f223ec6bc5
void HeapSort(ptrToItem arr[], int n);