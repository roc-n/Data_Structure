#include "../include/Stack.h"
int main(void)
{
    // 测试程序
    Stack S = CreateStack(100);
    for (int i = 0; i < 50; i++)
    {
        Push(i, S, 1);
        Push(i, S, 0);
    }
    cout << S->topOfStack_1 << "------" << S->topOfStack_2 << endl;
    int a = Top(S, 1);
    cout << a << endl;
    Pop(S, 1);
    int b = Top(S, 1);
    cout << b << "\nCapacity:" << S->capacity << endl;
    int c = TopAndPop(S, 1);
    for (int i = S->topOfStack_2; i < S->capacity; i++)
        cout << S->array[i] << endl;
    DisposeStack(S);
    cout << a << b << c << endl;
}