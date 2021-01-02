#ifndef _SORT_
#define _SORT_
#include "../include/User.h"
// 排序函数声明
void BubbleSort(ptrToItem arr[], int n);
void ChooseSort(ptrToItem arr[], int n);
void HeapSort(ptrToItem arr[], int n);
void InsertSort(ptrToItem arr[], int n);
void MergeSort(ptrToItem arr[], int n);
void QuickSort(ptrToItem arr[], int n);
void ShellSort(ptrToItem arr[], int n);
void RadixSort(ptrToItem arr[], int n);
// 判断函数
inline bool LessThan(ptrToItem &left, ptrToItem &right) {
  return left->num < right->num;
}
inline bool MoreThan(ptrToItem &left, ptrToItem &right) {
  return left->num > right->num;
}
inline bool Equal(ptrToItem &left, ptrToItem &right) {
  return left->num == right->num;
}
inline bool Less_EqualThan(ptrToItem &left, ptrToItem &right) {
  return left->num <= right->num;
}
inline bool More_EqualThan(ptrToItem &left, ptrToItem &right) {
  return left->num >= right->num;
}
// 倒序
void Inverse(ptrToItem arr[], int n);
#endif