#ifndef _LINKEDLIST_
#define _LINKEDLIST_
#include "../include/User.h"

// 定义节点
typedef struct node {
  Item itme;
  struct node *next;
} Node, *PtrToNode;

// 定义链表
typedef struct list {
  PtrToNode head;
  PtrToNode end;
  int items;
} List, *linkedList;
linkedList CreateList(linkedList &l);    //创建链表
void AddNode(linkedList &l);             //添加节点
void GetInfo(linkedList &l, Item &item); //得到信息
void Add(linkedList &l, Item &item);     //添加数据
bool IsEmpty(linkedList &l);             //判断链表是否为空
void Delete(linkedList &l);              //删除节点
ptrToItem Search(linkedList &l,int data);              //查找数据
void MakeEmpty(linkedList &l);           //清空链表
void Dispose(linkedList &l);             //销毁链表
#endif