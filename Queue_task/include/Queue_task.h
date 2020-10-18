/*
  声明文件
*/
#ifndef _QUEUE_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//定义任务结构
typedef struct task
{
  string name;
  int startTime;
  int totalTime = 0;
  int exe_start_time = 0;
  int exe_end_time = 0;
  int cnt = 0;
} Task;

//定义节点
typedef struct node
{
  Task item;
  struct node *next;
} Node;

//定义队列
typedef struct queue
{
  Node *head; //头节点
  Node *rear; //尾节点
  int items;  //节点数
  int max;    //可容纳的最大值
} Queue;
typedef Queue *Q;
void InitializeQueue(Q &pq, int &max); //初始化队列
void EnQueue(Q &pq, Task &item);       //进入队列
void DeQueue(Q &pq, Task &item);       //出队列
void MakeEmpty(Q &pq);                 //清空队列
void DisposeQueue(Q &pq);              //销毁队列
void ReadFile(Q &pq);                  //从文件中读入
void AddNode(Q &pq);                   //添加节点
void OutFile(Q &pq);                   //输出数据到文件
bool QueueIsFull(Q &pq);               //判断队列是否已满
bool QueueIsEmpty(Q &pq);              //判断队列是否为空
void HeadToRear(Q &pq, Node *&cur);    //将头节点调至尾部
#endif