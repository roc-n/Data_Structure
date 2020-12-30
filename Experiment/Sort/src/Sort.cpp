<<<<<<< HEAD
#include "../include/Sort.h"
// 交换函数
static void Swap(ptrToItem &a, ptrToItem &b);

static void Merge(ptrToItem *arr, ptrToItem *tmpArr, int l_pos, int r_pos,
                  int rightEnd);
static void MSort(ptrToItem arr[], ptrToItem tmpArr[], int left, int right);
static void PercDown(ptrToItem arr[], int pos, int n);


// 归并排序主函数
void MergeSort(ptrToItem arr[], int n) {
  ptrToItem *tmpArr = (ptrToItem *)malloc(sizeof(ptrToItem) * n);
  if (tmpArr != nullptr) {
    MSort(arr, tmpArr, 0, n - 1);
    free(tmpArr);
  } else {
    cout << "Error,out of space." << endl;
  }
}
// 快速排序主函数
void QuickSort(ptrToItem arr[], int l_pos, int r_pos) {
  if (r_pos - l_pos == 0 || r_pos - l_pos == -1) {
    return;
  }
  //   生成指定范围的随机数
  srand((unsigned int)time(0));
  int random = rand() % (r_pos - l_pos + 1) + l_pos;
  bool check = true;
  ptrToItem tmp = arr[random];//设定pivot值随机

  while (l_pos != r_pos) {
    if (check) {
      if (tmp->str[0] > arr[r_pos]->str[0]) {
        Swap(arr[l_pos], arr[r_pos]);
        check = false;
        l_pos++;
      } else {
        r_pos--;
      }
    } else {
      if (tmp->str[0] < arr[l_pos]->str[0]) {
        Swap(arr[l_pos], arr[r_pos]);
        check = true;
        r_pos--;
      }
      l_pos++;
    }
  }
  arr[l_pos] = tmp;
  // 左右两边递归排序
  QuickSort(arr, 0, l_pos - 1);
  QuickSort(arr, l_pos + 1, r_pos);
}
// 堆排序主函数
void HeapSort(ptrToItem arr[], int n) {
  for (int i = n / 2; i >= 0; i--) {
    PercDown(arr, i, n);
  }
  for (int i = n - 1; i > 0; i--) {
    Swap(arr[0], arr[i]);
    PercDown(arr, 0, i);
  }
}

static void Swap(ptrToItem &a, ptrToItem &b) {
  ptrToItem tmp = a;
  a = b;
  b = tmp;
}

// 堆排序的向下渗透
static void PercDown(ptrToItem arr[], int pos, int n) {
  ptrToItem tmp = arr[pos];
  int child;
  int i;
  for (i = pos; (2 * i + 1) < n; i = child) {
    child = (2 * i + 1);
    if (child != n - 1 && arr[child]->str[0] < arr[child + 1]->str[0]) {
      child++;
    }
    if (tmp->str[0] < arr[child]->str[0]) {
      arr[i] = arr[child];
    } else {
      break;
    }
  }
  arr[i] = tmp;
}
// 归并排序核心操作，对两个有序数组归并成新的有序数组
static void Merge(ptrToItem arr[], ptrToItem tmpArr[], int l_pos, int r_pos,
                  int rightEnd) {
  int i, leftEnd, num, tmpPos;
  leftEnd = r_pos - 1;
  tmpPos = l_pos;
  num = rightEnd - l_pos + 1;

  while (l_pos <= leftEnd && r_pos <= rightEnd) {
    if (arr[l_pos]->str[0] <= arr[r_pos]->str[0]) {
      tmpArr[tmpPos++] = arr[l_pos++];
    } else {
      tmpArr[tmpPos++] = arr[r_pos++];
    }
  } //   将剩下的有序项全部添加到tmpArr中
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
//递归排序的整体流程：分割再归并
static void MSort(ptrToItem arr[], ptrToItem tmpArr[], int left, int right) {
  int center;
  if (left < right) {
    center = (left + right) / 2;
    MSort(arr, tmpArr, left, center);
    MSort(arr, tmpArr, center + 1, right);
    Merge(arr, tmpArr, left, center + 1, right);
  }
=======
#include "../include/Sort.h"
// 交换函数
static void Swap(ptrToItem &a, ptrToItem &b);

static void Merge(ptrToItem *arr, ptrToItem *tmpArr, int l_pos, int r_pos,
                  int rightEnd);
static void MSort(ptrToItem arr[], ptrToItem tmpArr[], int left, int right);
static void PercDown(ptrToItem arr[], int pos, int n);


// 归并排序主函数
void MergeSort(ptrToItem arr[], int n) {
  ptrToItem *tmpArr = (ptrToItem *)malloc(sizeof(ptrToItem) * n);
  if (tmpArr != nullptr) {
    MSort(arr, tmpArr, 0, n - 1);
    free(tmpArr);
  } else {
    cout << "Error,out of space." << endl;
  }
}
// 快速排序主函数
void QuickSort(ptrToItem arr[], int l_pos, int r_pos) {
  if (r_pos - l_pos == 0 || r_pos - l_pos == -1) {
    return;
  }
  //   生成指定范围的随机数
  srand((unsigned int)time(0));
  int random = rand() % (r_pos - l_pos + 1) + l_pos;
  bool check = true;
  ptrToItem tmp = arr[random];//设定pivot值随机

  while (l_pos != r_pos) {
    if (check) {
      if (tmp->str[0] > arr[r_pos]->str[0]) {
        Swap(arr[l_pos], arr[r_pos]);
        check = false;
        l_pos++;
      } else {
        r_pos--;
      }
    } else {
      if (tmp->str[0] < arr[l_pos]->str[0]) {
        Swap(arr[l_pos], arr[r_pos]);
        check = true;
        r_pos--;
      }
      l_pos++;
    }
  }
  arr[l_pos] = tmp;
  // 左右两边递归排序
  QuickSort(arr, 0, l_pos - 1);
  QuickSort(arr, l_pos + 1, r_pos);
}
// 堆排序主函数
void HeapSort(ptrToItem arr[], int n) {
  for (int i = n / 2; i >= 0; i--) {
    PercDown(arr, i, n);
  }
  for (int i = n - 1; i > 0; i--) {
    Swap(arr[0], arr[i]);
    PercDown(arr, 0, i);
  }
}

static void Swap(ptrToItem &a, ptrToItem &b) {
  ptrToItem tmp = a;
  a = b;
  b = tmp;
}

// 堆排序的向下渗透
static void PercDown(ptrToItem arr[], int pos, int n) {
  ptrToItem tmp = arr[pos];
  int child;
  int i;
  for (i = pos; (2 * i + 1) < n; i = child) {
    child = (2 * i + 1);
    if (child != n - 1 && arr[child]->str[0] < arr[child + 1]->str[0]) {
      child++;
    }
    if (tmp->str[0] < arr[child]->str[0]) {
      arr[i] = arr[child];
    } else {
      break;
    }
  }
  arr[i] = tmp;
}
// 归并排序核心操作，对两个有序数组归并成新的有序数组
static void Merge(ptrToItem arr[], ptrToItem tmpArr[], int l_pos, int r_pos,
                  int rightEnd) {
  int i, leftEnd, num, tmpPos;
  leftEnd = r_pos - 1;
  tmpPos = l_pos;
  num = rightEnd - l_pos + 1;

  while (l_pos <= leftEnd && r_pos <= rightEnd) {
    if (arr[l_pos]->str[0] <= arr[r_pos]->str[0]) {
      tmpArr[tmpPos++] = arr[l_pos++];
    } else {
      tmpArr[tmpPos++] = arr[r_pos++];
    }
  } //   将剩下的有序项全部添加到tmpArr中
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
//递归排序的整体流程：分割再归并
static void MSort(ptrToItem arr[], ptrToItem tmpArr[], int left, int right) {
  int center;
  if (left < right) {
    center = (left + right) / 2;
    MSort(arr, tmpArr, left, center);
    MSort(arr, tmpArr, center + 1, right);
    Merge(arr, tmpArr, left, center + 1, right);
  }
>>>>>>> 558a2997b1b1b27da35cc1c92573a0f223ec6bc5
}