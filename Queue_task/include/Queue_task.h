#ifndef _QUEUE_TASK_H_
#include <initializer_list>
#ifndef _QUEUE_H_
#include <iostream>
#include <string>
using namespace std;
typedef struct task {
  string name;
  int startTime;
  int totalTime;
  int exe_start_time;
  int exe_end_time;
} Node;

typedef struct queue {
  Node *head;
  Node *rear;
} Queue;
void InitializeQueue(Queue *pq);
void EnQueue(Queue *pq);
void DeQueue(Queue *pq);
void DisposeQueue(Queue *pq);
void 

#endif