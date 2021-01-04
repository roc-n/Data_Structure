/*
  程序User类的各成员函数实现及辅助函数的实现
*/

#include "../include/User.h"
#include "../include/AvlTree.h"
#include "../include/Hash.h"
#include "../include/LinkedList.h"
#include "../include/Sort.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

string Sort[8] = {"InsertSort", "ShellSort", "HeapSort",   "RadixSort",
                  "QuickSort",  "MergeSort", "BubbleSort", "ChooseSort"};
//应用各排序函数对数据进行排序
static void ApplySort(ptrToItem arr[], int size);
// 应用链表搜索数据
static void ApplyListSearch(linkedList &l);
// 应用树结构搜索数据
static void ApplyTreeSearch(avlTree &T);
// 应用二分查找搜索数据
static void ApplyBinarySearch(ptrToItem arr[], int size);
// 应用哈希表查找数据
static void ApplyHashSearch(Hash &hash);

void User::Generate_Passsword_File() {
  fstream file;
  file.open("./include/user.txt", ios::in);
  if (file.fail()) {
    cout << "Error,Can't open file" << endl;
    return;
  }

  // 利用STL中map类构建密码字符串与出现次数的映射关系
  map<string, int> hash;
  string user_id, password;
  file >> user_id;
  file >> password;
  while (!file.eof()) {
    hash[password]++;
    // cout<<hash[password]<<endl;
    file >> user_id;
    file >> password;
  }
  file.close();
  file.open("./include/password.txt", ios::out);
  map<string, int>::iterator iter;
  Item item;
  for (iter = hash.begin(); iter != hash.end(); ++iter) {
    item.num = iter->second;
    item.password = iter->first;
    file << item.password << "\t" << item.num << endl;
  }
  cout << "Done" << endl;
  file.close();
}

void User::SortPassword() {
  ifstream in("./include/password.txt");
  if (in.fail()) {
    cout << "Can't open the file." << endl;
    return;
  }
  long number = 1300000;
  ptrToItem *arr = new ptrToItem[number];

  int size = 0;
  string password;
  int count;
  ptrToItem tmpItem;
  in >> password;
  in >> count;
  while (!in.eof()) {
    tmpItem = new Item;
    tmpItem->num = count;
    tmpItem->password = password;
    arr[size++] = tmpItem;
    in >> password;
    in >> count;
  }
  // 将读入的数组数据传入函数进行排序
  ApplySort(arr, size);
  // 将升序转化为降序
  Inverse(arr, size);
  // 输出出现次数最高的前20个密码
  for (int i = 0; i < 20; i++) {
    cout << "The top 20 passwords that occur the most times:\n"
         << arr[i]->password << ":  " << arr[i]->num << endl;
  }
  //内存回收
  for (int i = 0; i < size; i++) {
    delete arr[i];
  }
  delete[] arr;
}

static void ApplySort(ptrToItem arr[], int size) {
  // 创建函数指针数组,方便循环
  typedef void (*func)(ptrToItem *, int);
  // 这里只应用六种排序方式,其他两种太挫,耗时过长
  func func_ptr[6] = {InsertSort, ShellSort, HeapSort,
                      RadixSort,  QuickSort, MergeSort};
  // 分别执行对应排序函数,输出执行时间
  clock_t startTime, endTime;
  for (int i = 0; i < 6; i++) {
    startTime = clock();
    (*func_ptr[i])(arr, size);
    endTime = clock();
    cout << Sort[i] << "  " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << endl;
  }
}

void User::ReadToListAndSearch() {
  fstream in("./include/user.txt");
  if (in.fail()) {
    cout << "Can't open the file." << endl;
    return;
  }

  linkedList l;
  CreateList(l);
  Item tmp;

  in >> tmp.num;
  in >> tmp.password;
  while (!in.eof()) {
    Add(l, tmp);
    in >> tmp.num;
    in >> tmp.password;
  }
  ApplyListSearch(l);
  Dispose(l);
}

static void ApplyListSearch(linkedList &l) {
  int i;
  srand(time(0));
  // 存储随机的id
  int number;
  // 记录查找花费的总时间
  double totalTime = 0;
  clock_t startTime, endTime;
  // 存储查找返回的结果
  ptrToItem item;
  for (i = 0; i < 20; ++i) {
    number = rand() % 1250001;
    startTime = clock();
    item = Search(l, number);
    endTime = clock();
    if (item != nullptr) {
      totalTime += (double)(endTime - startTime) / CLOCKS_PER_SEC;
      cout << item->num << "\t" << item->password << endl;
    } else {
      cout << "Not find" << endl;
    }
  }
  for (i = 0; i < 5; ++i) {
    number = rand() % 1250001 + 1250001;
    startTime = clock();
    item = Search(l, number);
    endTime = clock();
    if (item != nullptr) {
      totalTime += (double)(endTime - startTime) / CLOCKS_PER_SEC;
      cout << item->num << "\t" << item->password << endl;
    } else {
      cout << "Not find" << endl;
    }
  }
  cout << "The search process costs " << totalTime << " s" << endl;
}

void User::ReadToTreeAndSearch() {
  fstream in("./include/user.txt");
  if (in.fail()) {
    cout << "Can't open the file." << endl;
    return;
  }

  avlTree T = nullptr;
  Item tmp;
  while (!in.eof() && in.peek() != EOF) {
    in >> tmp.num;
    in >> tmp.password;
    T = Insert(tmp, T);
    // cout << i++ << endl;
    in.get();
  }

  ApplyTreeSearch(T);
  MakeEMpty(T);
}

static void ApplyTreeSearch(avlTree &T) {
  int i;
  srand(time(0));
  // 存储随机的id
  int number;
  // 记录查找花费的总时间
  double totalTime = 0;
  clock_t startTime, endTime;
  // 存储查找返回的结果
  ptrToItem item;
  for (i = 0; i < 25; ++i) {
    // 生成随机数
    if (i < 20) {
      number = rand() % 1000001;
    } else {
      number = rand() % 1000001 + 10000001;
    }
    startTime = clock();
    item = Find(number, T);
    endTime = clock();
    if (item != nullptr) {
      totalTime += (double)(endTime - startTime) / CLOCKS_PER_SEC;
      cout << item->num << "\t" << item->password << endl;
    } else {
      cout << "Not find" << endl;
    }
  }
  cout << "The search process costs " << totalTime << " s" << endl;
}

void User::Generate_Userid_File() {
  fstream file;
  file.open("./include/user.txt", ios::in);
  if (file.fail()) {
    cout << "Erroe,Can't open the file." << endl;
    return;
  }

  ptrToItem *arr = (ptrToItem *)new ptrToItem[1250000];
  int size = 0;
  ptrToItem tmp;
  while (!file.eof() && file.peek() != EOF) {
    tmp = new Item;
    file >> tmp->num;
    file >> tmp->password;
    arr[size++] = tmp;
    file.get();
  }
  file.close();
  // 对id进行排序
  ApplySort(arr, size);
  // 排序结果输出到user_sorted.txt中
  file.open("./include/user_sorted.txt", ios::out);
  for (int i = 0; i < size; i++) {
    file << arr[i]->num << "\t" << arr[i]->password << endl;
  }
  file.close();
  //内存回收
  for (int i = 0; i < size; i++) {
    delete arr[i];
  }
  delete[] arr;
}

static void ApplyBinarySearch(ptrToItem arr[], int size) {
  int i;
  srand(time(0));
  // 存储随机的id
  int number;
  // 记录查找花费的总时间
  double totalTime = 0;
  clock_t startTime, endTime;
  // 存储查找返回的结果
  ptrToItem item;
  for (i = 0; i < 25; ++i) {
    // 生成随机数
    if (i < 20) {
      number = rand() % 1000001;
    } else {
      number = rand() % 1000001 + 10000001;
    }
    startTime = clock();
    item = BinarySearch(arr, size, number);
    endTime = clock();
    if (item != nullptr) {
      totalTime += (double)(endTime - startTime) / CLOCKS_PER_SEC;
      cout << item->num << "\t" << item->password << endl;
    } else {
      cout << "Not find" << endl;
    }
  }
  cout << "The search process costs " << totalTime << " s" << endl;
}

void User::BinarySearch() {
  fstream file;
  file.open("./include/user_sorted.txt", ios::in);
  if (file.fail()) {
    cout << "Erroe,Can't open the file." << endl;
    return;

    file.close();
  }

  ptrToItem *arr = (ptrToItem *)new ptrToItem[1250000];
  int size = 0;
  ptrToItem tmp;
  while (!file.eof() && file.peek() != EOF) {
    tmp = new Item;
    file >> tmp->num;
    file >> tmp->password;
    arr[size++] = tmp;
    file.get();
  }
  ApplyBinarySearch(arr, size);
}

ptrToItem BinarySearch(ptrToItem arr[], int size, int target) {
  // 记录当前查找位置
  int posi;
  int i = 0, j = size - 1;
  while (i <= j) {
    posi = (i + j) / 2;
    if (target == arr[posi]->num) {
      return arr[posi];
    } else if (target > arr[posi]->num) {
      i = posi + 1;
    } else {
      j = posi - 1;
    }
  }
  return nullptr;
}

void User::ReadToHash() {
  Hash hash;
  fstream file;
  file.open("./include/password.txt", ios::in);
  if (file.fail()) {
    cout << "Error,Can't open the file." << endl;
    return;
  }

  Item tmp;
  while (!file.eof() && file.peek() != EOF) {
    file >> tmp.num;
    file >> tmp.password;
    hash.Store(tmp);
    file.get();
  }
  // 辅助函数进行查找
  ApplyHashSearch(hash);
}

static void ApplyHashSearch(Hash &hash) {
  srand(time(0));
  string pwd;
  // 从pwd.txt中读取要查找的密码
  ifstream in("./include/pwd.txt");
  // 记录查找花费的总时间
  double totalTime = 0;
  clock_t startTime, endTime;
  // 存储查找返回的结果
  ptrToItem item;

  while (!in.eof() && in.peek() != EOF) {
    in >> pwd;
    startTime = clock();
    item = hash[pwd];
    endTime = clock();
    totalTime += (double)(endTime - startTime) / CLOCKS_PER_SEC;
    if (item != nullptr) {
      cout << item->password << "\t" << item->num << endl;
    } else {
      cout << "Not find" << endl;
    }
    in.get();
  }
  cout << "The search process costs " << totalTime << " s" << endl;
}
