/*
实现文件
*/

#include "../include/Queue_task.h"
#include <algorithm>

//本地函数
static void CopyToNode(Q &pq, Task &item);
static void CopyToItem(Q &pq, Task &item);

void InitializeQueue(Q &pq, int &max)
{
    pq = (Q)malloc(sizeof(Queue)); //为队列分配空间
    pq->head = pq->rear = NULL;
    pq->items = 0;
    pq->max = max;
}

void AddNode(Q &pq)
{
    if (QueueIsFull(pq))
    {
        cout << "The Queue is full!" << endl;
        return;
    }
    Node *newNode = (Node *)malloc(sizeof(Queue));
    if (!newNode)
    {
        fprintf(stdout, "Out of space!");
        exit(0); //内存占用已满，直接退出程序
    }
    if (!pq->items)
        pq->head = pq->rear = newNode;
    else
        pq->rear->next = newNode;
    pq->rear = newNode;
    pq->rear->next = NULL;
    pq->items++;
}

void EnQueue(Q &pq, Task &item)
{
    AddNode(pq);
    CopyToNode(pq, item); //添加节点并入队
}

void DeQueue(Q &pq, Task &item)
{
    if (QueueIsEmpty(pq))
    {
        cout << "Queue is empty!" << endl;
        return;
    }
    CopyToItem(pq, item);
    Node *tmp = pq->head;
    pq->head = pq->head->next;
    if (--pq->items == 0)
        pq->rear = NULL;
    free(tmp);
}

void DisposeQueue(Q &pq)
{
    MakeEmpty(pq);
    free(pq); //清空队列并释放内存
}

void MakeEmpty(Q &pq)
{
    while (!QueueIsEmpty(pq))
    {
        free(pq->head);
    }
    pq->items = 0;
}

//自定义排序标准
bool cmp(Node *a, Node *b)
{
    if (a->item.startTime < b->item.startTime)
    {
        return true;
    }
    return false;
}

//从文件读入
void ReadFile(Q &pq)
{
    fstream file;
    vector<Node *> arr; //暂时存储节点地址i的数组
    Node *tmp;          //暂时存储开辟的内存地址
    file.open("tasks.txt", ios::in);
    if (file.fail())
    {
        cout << "Can't open file." << endl;
        return;
    }
    while (!file.eof())
    {
        tmp = (Node *)new Node;
        file >> (tmp->item).name;
        file >> (tmp->item).startTime;
        file >> (tmp->item).totalTime;
        arr.push_back(tmp); //每循环一次将地址存入数组
    }
    sort(arr.begin(), arr.end(), cmp); //排序操作

    //将数组中的有序排列地址串起来
    pq->head = arr[0];
    pq->rear = arr.back();
    Node *cur = pq->head;
    for (unsigned int i = 0; i < arr.size(); i++)
    {
        if (pq->items == 0)
        {
            pq->head = pq->rear = arr[i];
        }
        else if ((unsigned int)pq->items == (arr.size() - 1))
        {
            cur->next = arr[i];
            pq->rear = arr[i];
            pq->rear->next = NULL;
        }
        else
        {
            cur->next = arr[i];
            cur = arr[i];
        }
        pq->items++;
    }
}

bool QueueIsEmpty(Q &pq)
{
    return pq->items == 0;
}

bool QueueIsFull(Q &pq)
{
    return pq->items == pq->max;
}
static void CopyToNode(Q &pq, Task &item)
{
    pq->rear->item = item;
}
static void CopyToItem(Q &pq, Task &item)
{
    item = pq->head->item;
}

//输出单个结点数据
void OutFile(Q &pq)
{
    fstream file;
    file.open("task_log.txt", ios::out | ios::app);
    Node *cur = pq->head;
    // while (cur)
    // {

    file << cur->item.name << " " << cur->item.exe_start_time << " "
         << cur->item.exe_end_time << " " << cur->item.cnt << endl;
    // cur = cur->next;
    // }
}

void HeadToRear(Q &pq, Node *&cur)
{
    pq->rear->next = cur;
    pq->rear = cur;
    cur = cur->next;
    pq->head = cur;
    pq->rear->next = NULL;
}
