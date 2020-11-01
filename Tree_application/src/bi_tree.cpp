#include "../include/bi_tree.h"
#include "../include/Stack.h"
#include "../include/queue.h"
#include <cstring>

static bool GetElements(string &postfix, string &str);
static void GetFileName(string &name);
// 中缀转后缀
string InfixToPostfix(string &nifix)
{

    // 创建两个栈，分别动态存储操作符与静态存储操作数
    Stack operations = CreateStack(20);
    Stack operators = CreateStack(20);

    stackItem tmpItem;   //定义栈数据域，ch进行存储
    ptrItem pt;          //定义指向栈数据域的指针，在出栈时进行存储
    string postfix = ""; //存储最后转化后的后缀表达式
    string str;
    char ch;
    // 从左向右遍历中缀表达式
    int i = 0;
    while (i != nifix.length())
    {
        ch = nifix[i];
        tmpItem.str = nifix[i];
        // 若字符为运算符
        if (IsOperators(nifix[i]))
        {
            if (ch == '(' || IsEmpty(operators)) //字符为'('或operators空栈时直接Push
            {
                Push(tmpItem, operators);
            }
            else if (ch == ')') //字符为')'时将()之间的所有operator Pop
            {
                pt = TopAndPop(operators);
                if (pt->str != "(")
                {
                    throw "Error";
                }
                while (pt->str != "(" && !IsEmpty(operators))
                {
                    Push(*pt, operations);
                    if (IsEmpty(operators))
                    {
                        break;
                    }
                    pt = TopAndPop(operators);
                }
                if (pt->str != "(")
                {
                    throw "Error";
                }
            }
            else if (IsAddOrSub(ch)) //字符为'+'或‘-’时将‘(’之前的所有operator Pop,或一直Pop到栈空，最后将自己Push
            {
                pt = Top(operators);
                while (!IsEmpty(operators) && pt->str != "(")
                {
                    Push(*pt, operations);
                    Pop(operators);
                    if (IsEmpty(operators))
                    {
                        break;
                    }
                    pt = Top(operators);
                }
                Push(tmpItem, operators);
            }
            else //字符为'*'或‘/’时将‘(’之前的优先级与它相等的或更高的operator Pop,或一直Pop到栈空,最后将自己Push
            {
                pt = Top(operators);
                while (!IsEmpty(operators) && pt->str != "(" && !IsAddOrSub(pt->str[0]))
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
            if (i != nifix.length() - 1)
            {
                int j = i + 1;
                char l = nifix[j];
                while (!IsOperators(l) && j != nifix.length())
                    l = nifix[++j];
                tmpItem.str = nifix.substr(i, j - i);
                i = j;
                Push(tmpItem, operations);
                continue;
            }
            else
                Push(tmpItem, operations);
        }
        i++;
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
    while (!IsEmpty(operations))
    {
        pt = TopAndPop(operations);
        postfix = pt->str + " " + postfix;
    }
    cout << postfix << endl;

    DisposeStack(operations);
    DisposeStack(operators);

    return postfix;
}

// 后缀转表达式树
PtrTrnode PostfixToExpression(string &postfix)
{
    Stack S = CreateStack(20); //创建临时栈以存储表达式的各部分
    stackItem curItem;         //临时栈的数据域，在这里提供树节点指针

    string str; //存储从后缀表达式提取出的元素
    ptrItem left, right;
    string postfix_copy = postfix;
    bool on = true; //决定什么时候退出循环
    while (on)
    {
        on = GetElements(postfix_copy, str);
        cout << str << endl;
        curItem.pt = MakeNode(str);

        if (IsOperators(str[0]))
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
        Push(curItem, S);
    }

    if (S->topOfStack != 0)
    {
        throw "Error";
    }

    DisposeStack(S);
    return curItem.pt;
}

bool IsOperators(char &ch)
{
    if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')')
        return true;
    return false;
}

PtrTrnode MakeNode(string &str)
{
    PtrTrnode newNode;
    newNode = new trnode;

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->expression = str;
    return newNode;
}

void Read(Tree &tr)
{
    fstream in;
    string name;
    GetFileName(name);
    in.open("include/" + name, ios::in);

    if (in.fail())
    {
        cout << "Error,Can't open the file.";
        return;
    }
    /*借助队列,层序创建完全二叉树*/

    int max = 200;                    //设定队列容量
    Queue *tmpQueue = InitQueue(max); //创建一个临时队列用以存储创建的节点
    Item tmpItem;                     //临时存储队列中的对象

    string tmpStr;
    PtrTrnode pt;  //存储新创建的节点
    PtrTrnode cur; //记录当前节点所在位置
    while (!in.eof())
    {
        in >> tmpStr;
        pt = MakeNode(tmpStr);
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
        tr->size++;
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
    int max = 200;             //暂时存储树节点队列的最大值
    Queue *Q = InitQueue(max); //定义存储树节点队列
    Item tmpItem;              //暂时存储队列节点信息
    tmpItem.pt = root;
    Item mid;
    int errorEx = 0, rightEx = 0; //记录正确与错误表达式数量

    if (root == NULL)
    {
        cout << "Empty Tree!" << endl;
        return;
    }

    EnQueue(tmpItem, Q); //将根结点入队
    while (!QueueIsEmpty(Q))
    {
        tmpItem.pt = DeQueue(Q);
        try
        {
            Manipulate(tmpItem.pt);
            rightEx++;
        }
        catch (const char *e)
        {
            errorEx++;
        }
        if (tmpItem.pt->left)
        {
            mid.pt = tmpItem.pt->left;
            EnQueue(mid, Q);
        }
        if (tmpItem.pt->right)
        {
            mid.pt = tmpItem.pt->right;
            EnQueue(mid, Q);
        }
    }

    Write(errorEx, rightEx);
}

double Compute(PtrTrnode &node)
{
    if (!node) //空节点返回0
    {
        return 0;
    }
    //递归调用，从叶子节点从左往右，从下往上计算
    double a = Compute(node->left);
    double b = Compute(node->right);
    char ch = node->expression[0];
    if (IsOperators(ch))
    {
        double result = results(node->expression, a, b);
        return result;
    }
    double num = stod(node->expression);
    return num;
}

double results(string &expression, double a, double b)
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

void Manipulate(PtrTrnode &node)
{
    string infix = node->expression;
    string postfix = InfixToPostfix(infix);
    PtrTrnode ExpressionRoot = PostfixToExpression(postfix);
    double result = Compute(ExpressionRoot);

    fstream out;
    out.open("include/A1_out.txt", ios::out | ios::app);

    if (int(result) == result)
    {
        result = int(result);
    }
    else
    {
        out << setiosflags(ios::fixed) << setprecision(4);
    }

    out << infix << "   "
        << "="
        << "  " << result << endl;
}

static bool GetElements(string &postfix, string &str)
{
    int index = postfix.find(' ');
    str = postfix.substr(0, index);
    if (postfix.length() - 1 == index)
        return false;
    postfix = postfix.substr(index + 1);
    return true;
}

static void GetFileName(string &name)
{
    cout << "Enter the name of file:" << endl;
    cin >> name;
}

void Write(int errorEx, int rightEx)
{
    fstream record;
    record.open("record.txt", ios::out);
    record << "执行运算时间：" << endl;
    record << "总的表达式数量为：" << rightEx + errorEx << endl;
    record << "正确表达式数量为 :  " << rightEx << endl;
    record << "错误表达式数量为：" << errorEx;
}