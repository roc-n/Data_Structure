#ifndef _STACK_H_
#define _STACK_H_
#include "../include/bi_tree.h"

struct StackRecord;                //栈相关数据
typedef struct StackRecord *Stack; //栈
typedef struct stackItem           //栈存储的数据域
{
    char ch;
    PtrTrnode pt;
    string str;
} * ptrItem;

struct StackRecord
{
    int capacity;   //栈容量
    int topOfStack; //指向栈顶
    ptrItem *array; //存储指向栈数据域的指针
    ptrItem wait;   //存储由TopAndPop函数产生的待释放指针
};

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(stackItem &x, Stack S);
void AddNode(Stack S);
ptrItem Top(Stack S);
void Pop(Stack S);
ptrItem TopAndPop(Stack S);
#endif