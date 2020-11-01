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
    S = (struct StackRecord *)new (struct StackRecord);
    // malloc error
    if (S == NULL)
    {
        cout << "Out of Space";
        return NULL;
    }
    S->array = (ptrItem *)malloc(sizeof(ptrItem) * MaxElements);
    // malloc error
    if (S->array == NULL)
    {
        cout << "Out of Space!" << endl;
        return NULL;
    }
    S->capacity = MaxElements;
    S->wait = NULL;
    S->topOfStack = -1;
    return S;
}

void MakeEmpty(Stack S)
{
    while (S->topOfStack != -1)
    {
        free(S->array[S->topOfStack--]);
    }
    if (S->wait != NULL)
    {
        free(S->wait);
    }
}

void DisposeStack(Stack S)
{
    MakeEmpty(S);
    if (S != NULL)
    {
        free(S->array);
        free(S);
    }
}

int IsEmpty(Stack S) { return S->topOfStack == Empty_0; }

int IsFull(Stack S) { return S->topOfStack == S->capacity; }

void Push(stackItem &x, Stack S)
{
    if (IsFull(S))
    {
        cout << "Full Stack!" << endl;
        return;
    }
    else
    {
        ptrItem newNode = new stackItem;
        *newNode = x;
        S->topOfStack++;
        S->array[S->topOfStack] = newNode;
    }
}

// pop the top data
ptrItem Top(Stack S)
{
    if (!IsEmpty(S))
        return S->array[S->topOfStack];
    cout << "Empty Stack!" << endl;
    return nullptr;
}

void Pop(Stack S)
{
    if (IsEmpty(S))
    {
        cout << "Empty Stack" << endl;
    }
    else
    {
        free(S->array[S->topOfStack--]);
    }
}

ptrItem TopAndPop(Stack S)
{
    if (S->wait != NULL)
    {
        free(S->wait);
    }
    if (!IsEmpty(S))
    {
        S->wait = S->array[S->topOfStack--];
        return S->wait;
    }
    cout << "Empty Stack" << endl;
    return nullptr;
}
