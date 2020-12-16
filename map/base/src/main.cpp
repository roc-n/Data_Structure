#include "../include/map_adjList.h"
#include "../include/map_adjMatrix.h"
#include <iostream>
#define MAX_V 50
using namespace std;

void MatrixToList(Matrix::Graph &map_m, Graph &map);
void ListToMatrix(Matrix::Graph &map_m, Graph &map);
int main(void) {
  // 邻接表实现输出所有路径
  Graph map;
  Init(map);
  Read(map);
  Display(map);
  SearchPath(map);
  DisPose(map);

  // 邻接表化矩阵
  Matrix::Graph map_m;
  Matrix::Init(map_m);
  Graph map_l;
  Init(map_l);
  Read(map_l);
  ListToMatrix(map_m, map_l);
  Matrix::Display_edge(map_m);
  DisPose(map_l);

  cout << "*********************************" << endl;
  cout << "*********************************" << endl;

  //矩阵化邻接表
  Graph map_list;
  Init(map_list);
  MatrixToList(map_m, map_list);
  Display(map_list);
  DisPose(map_list);
  return 0;
}

void MatrixToList(Matrix::Graph &map_m, Graph &map) {
  Vertex v1, v2;
  for (int i = 0; i < 6; i++) {
    v1.num = i + 1;
    map.adjList[map.vertex_num++].data = v1;
    for (int j = i; j < 6; j++) {
      if (map_m.edges[i][j] == 1) {
        v2.num = j;
        v1.degree += 2, v2.degree += 2;
        AddNode(map.adjList[i], j + 1);
        AddNode(map.adjList[j], i + 1);
        map.arc_num += 2;
      }
    }
  }
}

void ListToMatrix(Matrix::Graph &map_m, Graph &map) {
  Edge cur;
  for (int i = 0; i < map.vertex_num; i++) {
    cur = map.adjList[i].firstArc;
    while (cur != nullptr) {
      if (i < cur->vertex) {
        map_m.edges[i][cur->vertex - 1] = 1;
      } else {
        map_m.edges[cur->vertex - 1][i] = 1;
      }
      cur = cur->next;
    }
  }
}