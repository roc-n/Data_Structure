#ifndef _SORT_
#define _SORT_
#include "../include/User.h"
// 排序函数声明
void BubbleSort(ptrToItem arr[], int n);
void ChooseSort(ptrToItem arr[], int n);
void HeapSort(ptrToItem arr[], int n);
void InsertSort(ptrToItem arr[], int n);
void MergeSort(ptrToItem arr[], int n);
void QuickSort(ptrToItem arr[], int start, int end);
void ShellSort(ptrToItem arr[], int n);
void RadixSort(ptrToItem arr[], int n);
// 内联判断函数
bool LessThan(ptrToItem &left, ptrToItem &right);
bool MoreThan(ptrToItem &left, ptrToItem &right);
bool Equal(ptrToItem &left, ptrToItem &right);
bool Less_EqualThan(ptrToItem &left, ptrToItem &right);
bool More_EqualThan(ptrToItem &left, ptrToItem &right);
// 倒序
void Inverse(ptrToItem arr[], int n);
#endif