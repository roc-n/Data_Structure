#ifndef _STACK_H_
#define _STACK_H_
#include "../include/bi_tree.h"
#include <cstdlib>
#include <iostream>
using namespace std;

struct StackRecord;
typedef struct StackRecord *Stack;
typedef struct stackItem
{
    char ch;
    PtrTrnode pt;
} * ptrItem;

struct StackRecord
{
    int capacity;
    int topOfStack; //指向栈顶
    ptrItem array;
};

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(stackItem &x, Stack S);
ptrItem Top(Stack S);
void Pop(Stack S);
ptrItem TopAndPop(Stack S);
#endif