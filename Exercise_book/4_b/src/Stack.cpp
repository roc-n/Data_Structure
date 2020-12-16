#include "../include/Stack.h"
#define Empty_0 -1;
#define MinStackcSize 5

Stack CreateStack(int MaxElements)
{
    Stack S;
    // size should be big enough
    if (MaxElements < MinStackcSize)
    {
        cout << "Too small" << endl;
        return NULL;
    }
    S = (struct ShareStack *)new (struct ShareStack);
    // malloc error
    if (S == NULL)
    {
        cout << "Out of Space";
        return NULL;
    }
    S->array = (int *)malloc(sizeof(int) * MaxElements);
    // malloc error
    if (S->array == NULL)
    {
        cout << "Out of Space!" << endl;
        return NULL;
    }

    // 初始化操作
    S->capacity = MaxElements;
    S->topOfStack_1 = -1;
    S->topOfStack_2 = MaxElements;
    return S;
}

void MakeEmpty(Stack S, int which)
{
    // 顺序表中将下标移动以清空栈
    if (which)
    {
        S->topOfStack_2 = S->capacity;
    }
    else
    {
        S->topOfStack_1 = -1;
    }
}

void DisposeStack(Stack S)
{
    if (S != NULL)
    {
        free(S->array);
        free(S);
    }
}

int IsEmpty(Stack S, int which)
{
    if (which)
    {
        return S->topOfStack_2 == S->capacity;
    }
    else
    {
        return S->topOfStack_1 == -1;
    }
}
int IsFull(Stack S)
{
    // 若两栈下标相等则满
    return S->topOfStack_1 == S->topOfStack_2;
}

void Push(int x, Stack S, int which)
{
    if (IsFull(S))
    {
        cout << "Full Stack!" << endl;
        return;
    }
    else if (which)
    {
        S->array[--S->topOfStack_2] = x;
    }
    else
    {
        S->array[++S->topOfStack_1] = x;
    }
}

int Top(Stack S, int which)
{
    if (!IsEmpty(S, which))
    {
        if (which)
        {
            return S->array[S->topOfStack_2];
        }
        else
        {
            return S->array[S->topOfStack_1];
        }
    }
    cout << "Empty Stack!" << endl;
    return 0;
}

void Pop(Stack S, int which)
{
    if (IsEmpty(S, which))
    {
        cout << "Empty Stack" << endl;
    }
    else
    {
        // 通过移动下标来弹出
        if (which)
        {
            S->topOfStack_2++;
        }
        else
            S->topOfStack_1--;
    }
}

int TopAndPop(Stack S, int which)
{
    if (!IsEmpty(S, which))
    {
        if (which)
        {
            return S->array[S->topOfStack_2++];
        }
        else
        {
            return S->array[S->topOfStack_1--];
        }
    }
    cout << "Empty Stack" << endl;
    return 0;
}
