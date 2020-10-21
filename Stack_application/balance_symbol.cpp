#include <fstream>
#include <iostream>
using namespace std;

//定义节点
typedef struct node
{
    char ch;
    struct node *next;
} Node, *PtoNode;

typedef PtoNode Stack;

Stack CreateStack();              //创建栈
void Add(Stack &stack, char &in); //添加节点
bool IsEmpty(Stack &stack);       //判断是否为空
void MakeEmpty(Stack &stack);     //清空栈
void DisposeStack(Stack &stack);  //销毁栈
char Pop(Stack &stack);           //出栈
char check(char &ch);             //检测是否对应
// void ReadFile(Stack &stack);

int main(void)
{
    Stack s = CreateStack();
    bool right = false;
    fstream in;
    char ch; //暂时存储字符
    in.open("data.txt", ios::in);
    if (in.fail())
    {
        cout << "error,can't open file" << endl;
        return 0;
    }

    while (!in.eof())
    {
        in >> ch;
        if (ch == '{' || ch == '[' || ch == '(')
            Add(s, ch);
        else if (ch == '}' || ch == ']' || ch == ')')
        {
            if (IsEmpty(s))
                right = true;
            else if (check(ch) != Pop(s))
                right = true;
        }
    }
    if (!IsEmpty(s))
        right = true;
    if (right)
        cout << "Error" << endl;
    else
        cout << "No error." << endl;
}

Stack CreateStack()
{
    Stack stack = (PtoNode)malloc(sizeof(Node));
    stack->next = NULL;
    return stack;
}

void Add(Stack &stack, char &in)
{
    PtoNode newNode = (PtoNode)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        cout << "Out of Space!" << endl;
        exit(0);
    }

    newNode->next = stack->next;
    stack->next = newNode;
    newNode->ch = in;
}

// void ReadFile(Stack &stack)
// {
//     fstream in;
//     in.open("data.txt", ios::in);
//     if (in.fail())
//     {
//         cout << "error,can't open file" << endl;
//         return;
//     }

//     PtoNode cur = stack;
//     char ch;
//     while (in.eof())
//     {
//         in >> ch;
//         Add(stack, ch);
//     }
// }

bool IsEmpty(Stack &stack) { return stack->next == NULL; }

void MakeEmpty(Stack &stack)
{
    PtoNode cur = stack->next;
    PtoNode tmp;
    while (cur)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}

void DisposeStack(Stack &stack)
{
    MakeEmpty(stack);
    free(stack);
}

char Pop(Stack &stack)
{
    if (IsEmpty(stack))
    {
        cout << "Empty Stack!" << endl;
        return 'n';
    }
    else
    {
        PtoNode tmp = stack->next;
        char ch = stack->next->ch;
        stack->next = stack->next->next;
        free(tmp);
        return ch;
    }
}
char check(char &ch)
{
    if (ch == ']')
        return '[';
    else if (ch == '}')
        return '{';
    else
        return '(';
}
