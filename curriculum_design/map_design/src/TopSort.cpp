#include "../include/Map.h"
#include <iostream>
#include <queue>
using namespace std;
void TopSort(Map &map, int top_arr[]) {
  queue<Vertex> Q;
  // 记录入度为0的顶点数
  int counter = 0;
  int indegree_arr[map.vertex_num];
  Get_Indegree(map, indegree_arr);
  Vertex v, w;
  for (int i = 0; i < map.vertex_num; i++) {
    if (indegree_arr[i] == 0) {
      Q.push(map.adjList[i].v);
    }
  }
  while (!Q.empty()) {
    v = Q.front();
    Q.pop();
    top_arr[v.num] = ++counter;
    Edge cur = map.adjList[v.num].firstArc;
    while (cur != nullptr) {
      if (--indegree_arr[cur->end] == 0) {
        Q.push(map.adjList[cur->end].v);
      }
      cur = cur->next;
    }
  }
  // 若最后入度为0的点数量不为图的总顶点数则说明图有圈,不能进行拓扑排序
  if (counter != map.vertex_num) {
    cout << "Error,Graph has a circle,Can't topsort." << endl;
  }
}
void Get_Indegree(Map &map, int arr[]) {
  for (int i = 0; i < map.vertex_num; i++) {
    arr[i] = 0;
  }

  Edge cur;
  for (int i = 0; i < map.vertex_num; i++) {
    cur = map.adjList[i].firstArc;
    while (cur != nullptr) {
      arr[cur->end]++;
      cur = cur->next;
    }
  }
}

void DisplaySort(int top_arr[], int n) {
  cout << "The topsort is as follows:" << endl;
  for (int i = 0; i < n; i++) {
    cout << top_arr[i] << " ";
  }
  cout << endl;
}
