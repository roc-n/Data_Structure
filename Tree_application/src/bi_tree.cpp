#include "../include/bi_tree.h"
#include "../include/Stack.h"
#include "../include/queue.h"
#include <cstring>

// 中缀转后缀
string InfixToPostfix(string &nifix)
{
    // 创建两个栈，分别动态存储操作符与静态存储操作数
    Stack operations = CreateStack(20);
    Stack operators = CreateStack(20);

    stackItem tmpItem; //定义栈存储对象，ch进行存储
    ptrItem pt;        //定义指向栈存储对象的指针，在出栈时进行存储
    string postfix;    //存储最后转化后的后缀表达式

    string::iterator i; //创建迭代器
    // 从左向右遍历中缀表达式
    for (i = nifix.begin(); i != nifix.end(); ++i)
    {
        tmpItem.ch = *i;

        // 若字符为运算符
        if (IsOperators(*i))
        {
            if (*i == '(' || IsEmpty(operators)) //字符为'('或operators空栈时直接Push
            {
                Push(tmpItem, operators);
            }
            else if (*i == ')') //字符为')'时将()之间的所有operator Pop
            {
                pt = TopAndPop(operators);
                while (pt->ch != '(')
                    Push(*pt, operations);
            }
            else if (IsAddOrSub(*i)) //字符为'+'或‘-’时将‘(’之前的所有operator Pop,或一直Pop到栈空，最后将自己Push
            {
                pt = Top(operators);
                while (!IsEmpty(operators) && pt->ch != '(')
                {
                    Push(*pt, operations);
                    Pop(operators);
                    pt = Top(operators);
                }
                Push(tmpItem, operators);
            }
            else //字符为'*'或‘/’时将‘(’之前的优先级与它相等的或更高的operator Pop,或一直Pop到栈空,最后将自己Push
            {
                pt = Top(operators);
                while (!IsEmpty(operators) && pt->ch != '(' && !IsAddOrSub(pt->ch))
                {
                    Push(*pt, operations);
                    Pop(operators);
                    pt = Top(operators);
                }
                Push(tmpItem, operators);
            }
        }
        else //字符为数字直接push进操作数栈
        {
            Push(tmpItem, operations);
        }
    }

    //遍历结束后处理剩余的operator
    if (!IsEmpty(operators))
    {
        do
        {
            pt = TopAndPop(operators);
            Push(*pt, operations);
        } while (!IsEmpty(operators));
    }

    // 出栈并串接
    while (IsEmpty(operations))
    {
        pt = TopAndPop(operations);
        postfix += pt->ch;
    }
    reverse(postfix.begin(), postfix.end()); //恢复正向
    cout << postfix << endl;
    DisposeStack(operations);
    DisposeStack(operators);
    return postfix;
}
// 后缀转表达式树
PtrTrnode PostfixToExpression(string &postfix)
{
    Stack S = CreateStack(20);
    Tree ExpressionTr = CreateTree();
    int i;
    string str1, str2, str3, str;
    stackItem curItem;
    char ch;
    ptrItem left, right, root;

    for (i = 0; i != postfix.length(); ++i)
    {
        str = postfix.substr(i, 1);
        curItem.pt = MakeNode(str);
        ch = postfix[i];
        if (IsOperators(ch))
        {
            if (S->topOfStack < 1)
            {
                throw "Error";
            }
            right = TopAndPop(S);
            left = TopAndPop(S);
            curItem.pt->left = left->pt;
            curItem.pt->right = right->pt;
        }
        if (S->topOfStack != 0)
        {
            throw "Error";
        }
        Push(curItem, S);
    }

    return curItem.pt;
}

bool IsOperators(char &ch)
{
    if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')')
        return true;
    return false;
}

static PtrTrnode MakeNode(string &str)
{
    PtrTrnode newNode;
    newNode = new trnode; //

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->expression = str;
    return newNode;
}

void Read(Tree &tr)
{
    //借助队列创建完全二叉树
    fstream in;
    int max = 200;
    Queue *tmpQueue = InitQueue(max); //创建一个临时队列用以存储创建的节点
    Item tmpItem;                     //临时存储队列中的对象

    in.open("../include/data.txt", ios::in);
    if (in.fail())
    {
        throw "Error,Can't open the file.";
    }

    string tmp;
    in >> tmp;
    PtrTrnode pt;  //存储新创建的节点
    PtrTrnode cur; //记录当前节点所在位置
    while (!in.eof())
    {
        pt = MakeNode(tmp);
        if (tr->root == NULL) //当节点为根结点时
        {
            tr->root = pt;
            cur = tr->root;
        }
        else if (cur->left == NULL)
        {
            cur->left = pt;
            tmpItem.pt = cur->left;
            EnQueue(tmpItem, tmpQueue); //左孩子创建后继续创建右孩子
        }
        else if (cur->right == NULL)
        {
            cur->right = pt;
            tmpItem.pt = cur->right;
            EnQueue(tmpItem, tmpQueue);
            cur = DeQueue(tmpQueue); //右孩子创建后更新当前节点
        }
        in >> tmp;
    }
}

Tree CreateTree()
{
    Tree tr = new tree;
    tr->root = NULL;
    tr->size = 0;
    return tr;
}

void TraversalTree(PtrTrnode &root)
{

    int max = 200;
    Item tmp;
    tmp.pt = root;
    int errorEx, rightEx = 0;
    Queue *Q = InitQueue(max);
    if (root == NULL)
    {
        return;
    }
    EnQueue(tmp, Q);

    while (!QueueIsEmpty(Q))
    {
        tmp.pt = DeQueue(Q);
        try
        {
            manipulate(tmp.pt);
            rightEx++;
        }
        catch (const char *e)
        {
            errorEx++;
        }
        if (tmp.pt->left)
        {
            EnQueue(tmp, Q);
        }
        if (tmp.pt->right)
        {
            EnQueue(tmp, Q);
        }
    }

    fstream record;
    record.open("record.txt", ios::out);
    record << "执行运算时间：";
    record << "总的表达式数量为：" << rightEx + errorEx << endl;
    record << "正确表达式数量为 :   " << rightEx << endl;
    record << "错误表达式数量为：" << errorEx << endl;
}

int Compute(PtrTrnode &node)
{
    if (!node) //空节点返回0
    {
        return 0;
    }
    //递归调用，从叶子节点从左往右，从下往上计算
    int a = Compute(node->left);
    int b = Compute(node->right);
    char ch = node->expression[0];
    if (IsOperators(ch))
    {
        int result = results(node->expression, a, b);
        return result;
    }
    int num = stoi(node->expression);
    return num;
}

int results(string &expression, int a, int b)
{
    if (expression == "+")
    {
        return a + b;
    }
    else if (expression == "-")
    {
        return a - b;
    }
    else if (expression == "*")
    {
        return a * b;
    }
    else
    {
        return a / b;
    }
}

void DisPoseTree(PtrTrnode root)
{
    if (root)
    {
        DisPoseTree(root->left);
        DisPoseTree(root->right);
        delete root;
    }
}

bool IsAddOrSub(char &ch)
{
    if (ch == '+' || ch == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void manipulate(PtrTrnode &root)
{
    string infix = root->expression;
    string postfix = InfixToPostfix(infix);
    PtrTrnode ExpressionRoot = PostfixToExpression(postfix);
    int result = Compute(ExpressionRoot);

    fstream out;
    out.open("../include/src/A1_out.txt", ios::out | ios::app);
    out << infix << "   "
        << "=" << result;
}