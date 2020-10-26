#include <iostream>
using namespace std;

// 定义Item
typedef struct item
{
    int data;
    string name;
} Item;

// 定义节点
typedef struct node
{
    Item item;
    struct node *pre;
    struct node *next;
} Node, *PtrToNode;

//定义双向队列
typedef struct deque
{
    int size;
    PtrToNode head;
    PtrToNode rear;
} Deque, *PtrToQue;

// 创建双向队列
PtrToQue CreateQueue(void);
// 判断队列是否为空
bool IsEmpty(PtrToQue &q);
// 拷贝item到结点
void CopyToNode(Item item, PtrToNode pToNode);
// 从头部添加
void Push(Item x, PtrToQue &q);
// 从头部删除
Item Pop(PtrToQue &q);
// 从尾部添加
void Inject(Item x, PtrToQue &q);
// 从尾部删除
Item Eject(PtrToQue &q);

int main(void)
{
    // 测试程序
    PtrToQue q = CreateQueue();
    Item a[10];
    for (int i = 0; i < 10; i++)
    {
        a[i].data = 0;
        a[i].name = "Hello World!";
        Push(a[i], q);
    }
    for (int i = 0; i < 10; i++)
    {
        a[i].data = 1;
        a[i].name = "Hello World!";
        Inject(a[i], q);
    }
    cout << q->size << endl;

    // 异常处理
    try
    {
        Pop(q);
        Eject(q);
    }
    catch (const string msg)
    {
        cerr << msg << endl;
    }

    cout << q->size << endl;
    Item tmp;
    for (int i = 0; i < 18; i++) //此处q->size也在减
    {
        tmp = Pop(q);
        cout << tmp.data << "     " << tmp.name << endl;
    }
    cout << q->size << endl;
    return 0;
}

void CopyToNode(Item item, PtrToNode pToNode)
{
    pToNode->item = item;
}

bool IsEmpty(PtrToQue &q)
{
    return q->size == 0;
}

PtrToQue CreateQueue(void)
{
    PtrToQue q = (PtrToQue) new Deque;
    if (q == NULL)
    {
        cout << "Out of space!" << endl;
        exit(0);
    }
    // 初始化队列数据
    q->head = q->rear = NULL;
    q->size = 0;
    return q;
}

void Push(Item x, PtrToQue &q)
{
    PtrToNode newNode = (PtrToNode) new (Node);
    if (newNode == NULL)
    {
        cout << "Out of sapce!" << endl;
        exit(0);
    }

    newNode->pre = NULL;
    if (q->size == 0) //首次进队情况
    {
        q->head = q->rear = newNode;
        newNode->next = NULL;
    }
    else
    {
        //依次完成相关节点修改
        newNode->next = q->head;
        q->head->pre = newNode;
        q->head = newNode;
    }
    q->size++;
    CopyToNode(x, q->head);
}

Item Pop(PtrToQue &q)
{
    if (IsEmpty(q))
    {
        throw "Empty Queue!"; //抛出异常
    }

    // 存储数据
    Item tmp_item = q->head->item;
    PtrToNode tmp = q->head;
    q->head = q->head->next;
    delete tmp;
    q->size--;
    if (q->size == 0)
    {
        q->rear = NULL;
    }
    return tmp_item;
}

void Inject(Item x, PtrToQue &q)
{
    PtrToNode newNode = (PtrToNode) new (Node);
    if (newNode == NULL)
    {
        cout << "Out of sapce!" << endl;
        exit(0);
    }

    newNode->next = NULL;
    if (q->size == 0)
    {
        q->head = q->rear = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->pre = q->rear;
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    CopyToNode(x, q->rear);
}

Item Eject(PtrToQue &q)
{
    if (IsEmpty(q))
    {
        throw "Empty Queue!";
    }

    Item tmp_item = q->rear->item;
    PtrToNode tmp = q->rear;
    q->rear = q->rear->pre;
    delete tmp;
    q->size--;
    if (q->size == 0)
    {
        q->head = NULL;
    }
    return tmp_item;
}