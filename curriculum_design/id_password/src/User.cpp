#include "../include/User.h"
#include "../include/AvlTree.h"
#include "../include/LinkedList.h"
#include "../include/Sort.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

string Sort[8] = {"InsertSort", "ShellSort", "HeapSort",
                  "RadixSort",  "QuickSort", "MergeSort"};
static void ApplySort(ptrToItem arr[], int size);
static void ApplyListSearch(linkedList &l);
static void ApplyTreeSearch(avlTree &T);
static void ApplyBinarySearch(ptrToItem arr[], int size);
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
  func func_ptr[6] = {InsertSort, ShellSort, HeapSort,
                      RadixSort,  QuickSort, MergeSort};
  // 分别执行对应排序函数,输出执行时间
  clock_t startTime, endTime;
  for (int i = 0; i < 6; i++) {
    startTime = clock();
    (*func_ptr[i])(arr, size);
    endTime = clock();
    cout << Sort[i] << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
  }
}

void User::ReadToList() {
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
    Search(l, number);
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

void User::ReadToTree() {
  fstream in("./include/user.txt");
  if (in.fail()) {
    cout << "Can't open the file." << endl;
    return;
  }

  avlTree T = nullptr;
  Item tmp;

  in >> tmp.num;
  in >> tmp.password;
  while (!in.eof()) {
    T = Insert(tmp, T);
    in >> tmp.num;
    in >> tmp.password;
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
  for (i = 0; i < 20; ++i) {
    number = rand() % 1250001;
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
  for (i = 0; i < 5; ++i) {
    number = rand() % 1250001 + 1250001;
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
  ApplySort(arr, size);

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
  for (i = 0; i < 20; ++i) {
    number = rand() % 1250001;
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
  for (i = 0; i < 5; ++i) {
    number = rand() % 1250001 + 1250001;
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

ptrToItem BinarySearch(ptrToItem arr[], int size, int target) {
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