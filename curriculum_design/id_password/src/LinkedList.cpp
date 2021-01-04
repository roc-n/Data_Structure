#include "../include/LinkedList.h"
#include <iostream>
using namespace std;
linkedList CreateList(linkedList &l) {
  l = (linkedList)malloc(sizeof(List));
  if (l == NULL) {
    cout << "Out of space!" << endl;
    exit(0);
  }

  l->head = l->end = NULL;
  l->items = 0;
  return l;
}

void AddNode(linkedList &l) {
  PtrToNode newNode = new Node;
  newNode->next = NULL;
  if (l->items == 0)
    l->head = l->end = newNode;
  else {
    l->end->next = newNode;
    l->end = newNode;
  }
  l->items++;
}

void Add(linkedList &l, Item &item) {
  AddNode(l);
  GetInfo(l, item);
}

void GetInfo(linkedList &l, Item &item) { l->end->itme = item; }

bool IsEmpty(linkedList &l) { return l->items == 0; }

void Delete(linkedList &l) {
  // 查找操作
  int data;
  cout << "Enter the data to delete." << endl;
  cin >> data;
  PtrToNode currentNode = l->head;
  PtrToNode preNode = NULL;
  while (currentNode) {
    if (currentNode->itme.num == data)
      break;
    preNode = currentNode;
    currentNode = currentNode->next;
  }

  // 删除操作
  if (currentNode == l->head) {
    l->head = currentNode->next;
    free(currentNode);
  } else if (currentNode == l->end) {
    preNode->next = NULL;
    l->end = preNode;
  }

  else if (currentNode == NULL) {
    cout << "Not find,Can't delete." << endl;
    return;
  } else {
    preNode->next = currentNode->next;
    free(currentNode);
  }
  cout << "Done" << endl;
}

ptrToItem Search(linkedList &l, int data) {
  PtrToNode currentNode = l->head;
  while (currentNode) {
    if (currentNode->itme.num == data) {
      return &currentNode->itme;
    }
    currentNode = currentNode->next;
  }
  return nullptr;
}

void MakeEmpty(linkedList &l) {
  PtrToNode currentNode = l->head;
  PtrToNode tmp;
  while (currentNode) {
    tmp = currentNode;
    currentNode = currentNode->next;
    delete tmp;
    // cout << i++ << endl;
  }
}

void Dispose(linkedList &l) {
  MakeEmpty(l);
  free(l);
}