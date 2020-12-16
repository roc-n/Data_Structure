#ifndef _STACK_H_
#define _STACK_H_
#include <cstdlib>
#include <iostream>
using namespace std;

// 定义共享栈
struct ShareStack;
typedef struct ShareStack *Stack;
struct ShareStack
{
    int capacity;
    int topOfStack_1;
    int topOfStack_2;
    int *array;
};

//判断栈是否为空
int IsEmpty(Stack S, int which);
//判断栈是否为满
int IsFull(Stack S);
// 创建栈
Stack CreateStack(int MaxElements);
// 销毁栈
void DisposeStack(Stack S);
// 清空栈
void MakeEmpty(Stack S, int which);
// 进栈
void Push(int x, Stack S, int which);
// 提取栈顶元素
int Top(Stack S, int which);
// 出栈
void Pop(Stack S, int which);
// 出栈并提取栈顶元素
int TopAndPop(Stack S, int which);
#endif