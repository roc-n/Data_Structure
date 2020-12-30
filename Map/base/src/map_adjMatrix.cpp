#include "../include/map_adjMatrix.h"
#include <fstream>
#include <iostream>
using namespace std;
void Matrix::Init(Graph &map) {
  map.vertex_num = map.arc_num = 0;
  for (int i = 0; i < MAX_V; i++) {
    for (int j = 0; j < MAX_V; j++) {
      map.edges[i][j] = 0;
    }
  }
}

void Matrix::Read(Graph &map) {

  fstream in;
  in.open("data.txt", ios::in);
  //   编号
  string number;
  //   起点，终点()
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
        map.vex[map.vertex_num++] = v;
      }
      while (!in.eof()) {
        in >> v1;
        if (!in.eof()) {
          in >> v2;
        } else {
          break;
        }
        map.arc_num++;
        //  无向图只存储于矩阵的上三角
        if (v1 <= v2)
          map.edges[v1 - 1][v2 - 1] = 1;
        else
          map.edges[v2 - 1][v1 - 1] = 1;
      }
    } else {
      cout << "Format Error." << endl;
    }
  }
  in.close();
}

void Matrix::Display_edge(Graph &map) {
  for (int i = 0; i < MAX_V; i++) {
    for (int j = 0; j < MAX_V; j++) {
      if (i <= j && map.edges[i][j] == 1) {
        cout << "There is an edge between " << i + 1 << " and " << j + 1
             << endl;
      }
    }
  }
}