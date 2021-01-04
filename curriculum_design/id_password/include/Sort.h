/*
  八个排序函数与五个判断函数的声明文件，判断使用内联函数封装，可依据需要自定义排序依据
*/

#ifndef _SORT_
#define _SORT_
#include "../include/User.h"
// 排序函数声明

//冒泡排序
void BubbleSort(ptrToItem arr[], int n);
// 选择排序
void ChooseSort(ptrToItem arr[], int n);
// 堆排序
void HeapSort(ptrToItem arr[], int n);
// 插入排序
void InsertSort(ptrToItem arr[], int n);
// 归并排序
void MergeSort(ptrToItem arr[], int n);
// 快速排序
void QuickSort(ptrToItem arr[], int n);
// 希尔排序
void ShellSort(ptrToItem arr[], int n);
// 基数排序
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