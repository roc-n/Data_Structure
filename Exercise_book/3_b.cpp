#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

/*声明与定义*/
#define max 100

typedef struct node
{
    int data;
    struct node *next;
} node_, *Node;

//定义链表结构
typedef struct list
{
    int size;
    Node head;
    Node end;
    int Max;
} linked, *List;

void Add(int &a, List &list);                  //添加数据到顺序表
void AddNode(List &list);                      //添加数据节点
bool IsEmpty(List &list);                      //判断是否为空
bool IsFull(List &list);                       //判断是否为满
List &CreateList(List &list);                  //创建一个顺序表
void Find(List &list, int &num);               //查找指定元素，找到则返回下标值
void ToHead(List &list, Node &pos, Node &pre); //查找后将查找元素调至表头
void MakeEmpty(List &list);                    //清空顺序表
void DisposeList(List &list);                  //销毁顺序表

/*测试程序*/
int main(void)
{
    List l = CreateList(l);
    for (int i = 0; i < max; i++)
        Add(i, l);
    Node cur = l->head;
    while (cur != NULL)
    {
        cout << cur->data << endl;
        cur = cur->next;
    }
    int check = 99;
    Find(l, check);
    check = 0;
    Find(l, check);
    check = 97;
    Find(l, check);
//     check = 100;
//     Find(l, check);
//     DisposeList(l);
//     return 0;
// }
}
/*实现*/
List &CreateList(List &list)
{
    list = (List) new linked;
    list->size = 0;
    list->head = list->end = NULL;
    list->Max = max;
    return list;
}
void Add(int &a, List &list)
{
    //异常处理机制
    if (IsFull(list))
    {
        cout << "The list is full!" << endl;
        return;
    }
    AddNode(list);
    list->head->data = a;
    list->size++;
}

void MakeEmpty(List &list)
{
    Node cur = list->head;
    Node tmp;
    while (cur != NULL)
    {
        tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

void DisposeList(List &list)
{
    MakeEmpty(list);
    delete list;
}
bool IsFull(List &list)
{
    return list->size == list->Max;
}

bool IsEmpty(List &list)
{
    return list->size == 0;
}

void Find(List &list, int &num)
{
    if (IsEmpty(list))
    {
        cout << "The list is Empty!" << endl;
        return;
    }
    Node cur = list->head;
    Node pre = list->head;
    while (cur)
    {
        if (cur->data == num)
        {
            cout << "Find it!" << endl;
            ToHead(list, cur, pre);
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    cout << "Not find." << endl;
    return;
}

void ToHead(List &list, Node &pos, Node &pre)
{
    if (pos==list->head) {
        return;
    }
    if (pos==list->end) {
        list->end = pre;
    }
    pre->next = pos->next;
    pos->next = list->head;
    list->head = pos;
}

void AddNode(List &list)
{
    Node newNode = (Node) new node_;
    if (newNode == NULL)
    {
        cout << "Out of space!" << endl;
        exit(0);
    }
    if (list->size == 0)
    {
        list->head = list->end = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = list->head;
        list->head = newNode;
    }
}