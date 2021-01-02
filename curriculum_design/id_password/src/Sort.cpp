#include "../include/Sort.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
/*
快速排序辅助函数
*/
static ptrToItem GetPivot(ptrToItem arr[], int start,
                          int end);           // 三数-中值法得到枢纽元
static void Swap(ptrToItem &a, ptrToItem &b); //交换值
static void QuickSortCore(ptrToItem *arr, int start, int end);
/*
堆排序辅助函数
*/
#define LeftChild(i) (2 * (i) + 1)
void PercDown(ptrToItem arr[], int position, int n); // 最大堆向下渗透
/*
归并排序辅助函数
*/
static void MSort(ptrToItem arr[], ptrToItem tmpArr[], int left,
                  int right); //归并排序的整体流程：分割再归并

void Merge(
    ptrToItem arr[], ptrToItem tmpArr[], int l_pos, int r_pos,
    int rightEnd); // 操作的核心，将两个已排好序的数组归并为新的有序数组（利用双指针法）
// l_poos,r_pos,LeftEnd,rightEnd是为标记数组中的位置，tmpPos标记tmpArr的位置

/*
基数排序辅助函数
*/
void CountSort(ptrToItem arr[], int n, int exp); //计数排序
ptrToItem GetMax(ptrToItem arr[], int n);        //取得最大值

/*
函数实现
*/
void InsertSort(ptrToItem arr[], int n) {
  int j, p;
  ptrToItem tmp;
  for (p = 1; p < n; p++) {
    tmp = arr[p];
    for (j = p; j > 0 && LessThan(tmp, arr[j - 1]); j--) {
      arr[j] = arr[j - 1];
    }
    arr[j] = tmp;
  }
}

void ShellSort(ptrToItem arr[], int n) {
  // increment为跨度
  int i, j, increment;
  Item item;
  ptrToItem tmp;
  for (increment = n / 2; increment > 0; increment /= 2) {
    for (i = increment; i < n; i++) {
      tmp = arr[i];
      // 局部插入排序
      for (j = i; j >= increment; j -= increment) {
        if (LessThan(tmp, arr[j - increment])) {
          arr[j] = arr[j - increment];
        } else {
          break;
        }
      }
      arr[j] = tmp;
    }
  }
}

void QuickSortCore(ptrToItem arr[], int start, int end) {
  // 出口条件,即只有一个或两个待排数据
  if (end - start == 1 || end == start) {
    if (LessThan(arr[end], arr[start])) {
      Swap(arr[end], arr[start]);
    }
    return;
  }

  ptrToItem pivot;
  // 得到pivot
  pivot = GetPivot(arr, start, end);
  int i = start + 1;
  int j = end - 2;
  bool rightToLeft = true;
  // 主要操作,左右指针反复横跳
  while (j - i != -1) {
    if (rightToLeft) {
      // 相等时亦进行跳转，防止极端情况的发生
      if (Less_EqualThan(arr[j], pivot)) {
        Swap(arr[i], arr[j]);
        i++;
        rightToLeft = false;
      } else {
        j--;
      }
    } else {
      if (More_EqualThan(arr[i], pivot)) {
        Swap(arr[i], arr[j]);
        j--;
        rightToLeft = true;
      } else {
        i++;
      }
    }
  }
  // 将pivot与i处数据交换完成排序
  Swap(arr[i], arr[end]);
  // 递归排序左右两边
  QuickSortCore(arr, start, j);
  QuickSortCore(arr, i + 1, end);
}

void QuickSort(ptrToItem arr[], int n) { QuickSortCore(arr, 0, n - 1); }

static ptrToItem GetPivot(ptrToItem arr[], int start, int end) {
  int left = arr[start]->num;
  int right = arr[end]->num;
  int median = arr[(start + end) / 2]->num;
  int max, min, medium;
  // 先比较两数之间的大小关系并记录
  if (left > right) {
    max = left;
    min = right;
  } else {
    max = right;
    min = left;
  }
  // 再比较第三个数与前两个数的大小关系
  if (max < median) {
    medium = max;
    max = median;
  } else if (median > min) {
    medium = median;
  } else {
    medium = min;
    min = median;
  }
  // 将三个位置重新赋值
  arr[start]->num = min;
  arr[(start + end) / 2]->num = max;
  arr[end]->num = medium;
  // 交换end-1处与max处
  Swap(arr[end - 1], arr[(start + end) / 2]);
  return arr[end];
}

static void Swap(ptrToItem &a, ptrToItem &b) {
  ptrToItem tmp = a;
  a = b;
  b = tmp;
}

void PercDown(ptrToItem arr[], int position, int n) {
  ptrToItem tmp = arr[position]; //暂时存储向下渗透的节点
  int child;
  for (tmp = arr[position]; LeftChild(position) < n; position = child) {
    child = LeftChild(position);
    if (child != n - 1 && LessThan(arr[child], arr[child + 1])) {
      child++;
    }
    if (LessThan(tmp, arr[child])) {
      arr[position] = arr[child];
    } else { //一旦不满足条件即可根据二叉堆的性质判断出无需再下渗
      break;
    }
  }
  arr[position] = tmp; //找到位置后填进去
}

void HeapSort(ptrToItem arr[], int n) {
  for (int i = n / 2; i >= 0; i--) {
    PercDown(arr, i, n); //构建最大堆
  }
  //   进行排序,每次将当前最大的项放在数组末端
  for (int i = n - 1; i > 0; i--) {
    Swap(arr[0], arr[i]);
    PercDown(arr, 0, i);
  }
}

void Merge(ptrToItem arr[], ptrToItem tmpArr[], int l_pos, int r_pos,
           int rightEnd) {
  int i, leftEnd, num, tmpPos;
  leftEnd = r_pos - 1;
  tmpPos = l_pos;
  num = rightEnd - l_pos + 1;

  while (l_pos <= leftEnd && r_pos <= rightEnd) {
    if (LessThan(arr[l_pos], arr[r_pos])) {
      tmpArr[tmpPos++] = arr[l_pos++];
    } else {
      tmpArr[tmpPos++] = arr[r_pos++];
    }
  }

  //   将剩下的有序项全部添加到tmpArr中
  while (l_pos <= leftEnd) {
    tmpArr[tmpPos++] = arr[l_pos++];
  }
  while (r_pos <= rightEnd) {
    tmpArr[tmpPos++] = arr[r_pos++];
  }

  //   将tmpArr存储的值拷贝回原数组（若用链表实现则不需要）
  for (i = 0; i < num; i++, rightEnd--) {
    arr[rightEnd] = tmpArr[rightEnd];
  }
}

static void MSort(ptrToItem arr[], ptrToItem tmpArr[], int left, int right) {
  int center;
  if (left < right) {
    center = (left + right) / 2;
    MSort(arr, tmpArr, left, center);
    MSort(arr, tmpArr, center + 1, right);
    Merge(arr, tmpArr, left, center + 1, right);
  }
}

void MergeSort(ptrToItem arr[], int n) {
  ptrToItem *tmpArr = (ptrToItem *)malloc(sizeof(ptrToItem) * n);
  if (tmpArr != nullptr) {
    MSort(arr, tmpArr, 0, n - 1);
    free(tmpArr);
  } else {
    cout << "Error,out of space." << endl;
  }
}

void BubbleSort(ptrToItem arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    cout << i << endl;
    for (int j = 0; j < n - 1; j++) {
      if (LessThan(arr[j + 1], arr[j])) {
        Swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void ChooseSort(ptrToItem arr[], int n) {
  ptrToItem min;
  int min_index;
  int i, j;
  i = 0;
  for (i = 0; i < n - 1; i++) {
    min = arr[i];
    min_index = i;
    cout << i << endl;
    for (j = i + 1; j < n; j++) {
      if (LessThan(arr[j], min)) {
        min = arr[j];
        min_index = j;
      }
    }
    Swap(arr[min_index], arr[i]);
  }
  cout << "You are right" << endl;
}

ptrToItem GetMax(ptrToItem arr[], int n) {
  ptrToItem max = arr[0];
  for (int i = 1; i < n; i++) {
    if (MoreThan(arr[i], max)) {
      max = arr[i];
    }
  }
  return max;
}

void CountSort(ptrToItem arr[], int n, int exp) {
  unique_ptr<ptrToItem[]> output(new ptrToItem[n]);
  int i = 0;
  int buckets[10] = {0};
  for (i = 0; i < n; i++) {
    buckets[(arr[i]->num / exp) % 10]++;
  }
  for (i = 1; i < 10; i++) {
    buckets[i] += buckets[i - 1];
  }

  for (i = n - 1; i >= 0; i--) {
    output[buckets[(arr[i]->num / exp) % 10] - 1] = arr[i];
    buckets[(arr[i]->num / exp) % 10]--;
  }
  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
  }
}

void RadixSort(ptrToItem arr[], int n) {
  ptrToItem max = GetMax(arr, n);
  int exp;
  for (exp = 1; max->num / exp != 0; exp *= 10) {
    CountSort(arr, n, exp);
  }
}

void Inverse(ptrToItem arr[], int n) {
  int pivot = (0 + n) / 2;
  for (int i = 0; i < pivot; i++) {
    Swap(arr[i], arr[n - 1 - i]);
  }
}

