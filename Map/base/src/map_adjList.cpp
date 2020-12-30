#include "../include/map_adjList.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
//  递归查找路径
static void FindPath(Graph &map, int start, int end, std::vector<int> &arr,
                     bool &findIt);
void Init(Graph &map) {
  map.vertex_num = map.arc_num = 0;
  for (int i = 0; i < MAX_V; i++) {
    map.adjList[i].data.num = 0;
    map.adjList[i].data.degree = 0;
    map.adjList[i].firstArc = map.adjList[i].lastArc = nullptr;
  }
}

void Read(Graph &map) {
  fstream in;
  in.open("data/data.txt", ios::in);
  //   编号
  string number;
  //   起点，终点(无向图即重合)
  int v1, v2;

  Vertex v;
  if (in.fail()) {
    cout << "Fail to open the file" << endl;
  } else {
    in >> number;
    if (number == "vertices:") {
      while (!in.eof()) {
        in >> number;
        if (number == "edges:")
          break;
        v.num = stoi(number);
        map.adjList[map.vertex_num++].data = v;
      }
      while (!in.eof()) {
        in >> v1;
        if (!in.eof()) {
          in >> v2;
        } else {
          break;
        }
        AddNode(map.adjList[v1 - 1], v2);
        map.arc_num++;
        map.adjList[v1 - 1].data.degree++;
      }
    } else {
      cout << "Format Error." << endl;
    }
  }
  in.close();
}

void Display(Graph &map) {
  Edge cur;
  for (int i = 0; i < map.vertex_num; i++) {
    cur = map.adjList[i].firstArc;
    while (cur != nullptr) {
      cout << "There is an edge between " << map.adjList[i].data.num << " and "
           << cur->vertex << endl;
      cur = cur->next;
    }
  }
  cout << "There are " << map.vertex_num << "  vertices and " << map.arc_num
       << " edges" << endl;
}

void AddNode(VNode &vNode, int vertex) {
  Edge newArc = new ArcNode;
  newArc->vertex = vertex;
  newArc->next = nullptr;

  if (vNode.firstArc == nullptr) {
    vNode.firstArc = vNode.lastArc = newArc;
  } else {
    vNode.lastArc->next = newArc;
    vNode.lastArc = newArc;
  }
}

void DisPose(Graph &map) {
  Edge cur;
  Edge tmp;
  for (int i = 0; i < map.vertex_num; i++) {
    cur = map.adjList[i].firstArc;
    while (cur != nullptr) {
      tmp = cur->next;
      delete cur;
      cur = tmp;
    }
  }
}

static void FindPath(Graph &map, int start, int end, vector<int> &arr,
                     bool &findIt) {

  Edge cur = map.adjList[start - 1].firstArc;
  bool check = true; //检测当前的顶点是否已走过
  //   每次进入新的表头节点便添加到arr进行跟踪
  arr.push_back(start);
  while (cur != nullptr) {
    //   找到终点
    if (cur->vertex == end) {
      arr.push_back(end);
      cout << "One path is:" << endl;
      for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
      }
      cout << endl;
      arr.pop_back();
      findIt = true; //确定至少有一条路径
    } else {
      for (int i = 0; i < arr.size(); i++) {
        if (cur->vertex == arr[i]) {
          check = false;
          break;
        }
      }
      if (check) {
        //   进入下一个顶点进行搜寻
        FindPath(map, cur->vertex, end, arr, findIt);
      }
    }
    cur = cur->next;
    check = true;
  }
  arr.pop_back();
}

void SearchPath(Graph &map) {
  cout << "Enter two integers:" << endl;
  vector<int> arr;
  int a, b;
  bool findIt;
  cin >> a >> b;
  int start = min(a, b);
  int end = max(a, b);
  FindPath(map, start, end, arr, findIt);
  if (findIt) {
    cout << "Done" << endl;
  } else {
    cout << "Not find" << endl;
  }
}