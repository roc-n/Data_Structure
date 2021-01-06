#include "../include/Map.h"
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

void Map::Read() {
  fstream in;
  in.open("../include/data.txt", ios::in);
  // 顶点代号
  string code_name;
  // 暂时存储从文件读入的边和顶点信息
  ArcNode arc;
  Vertex v;
  // 存储边的起点与终点
  int start, end;
  if (in.fail()) {
    cout << "Fail to open the file" << endl;
  } else {
    in >> code_name;
    if (code_name == "vertices:") {
      while (!in.eof() && in.peek() != EOF) {
        in >> code_name;
        // 判断顶点是否已读完毕
        if (code_name == "edges:") {
          break;
        }
        in >> v.credit;
        v.code_name = code_name;
        v.num = vertex_num; //确定顶点内部编号
        hash[code_name] = vertex_num; //构建顶点字符串与内部编号的映射关系
        adjList[vertex_num++].v = v;
        in.get();
      }
      while (!in.eof() && in.peek() != EOF) {
        in >> code_name;
        start = hash[code_name];
        in >> code_name;
        end = hash[code_name];
        arc.end = end;
        AddArcNode(adjList[start], arc);
        arc_num++;
        in.get();
      }
    } else {
      cout << "Format Error." << endl;
    }
  }
  in.close();
}

void Map::Display_edge() {
  Edge cur;
  for (int i = 0; i < vertex_num; i++) {
    cur = adjList[i].firstArc;
    while (cur != nullptr) {
      cout << "There is an edge between " << adjList[i].v.code_name << " and "
           << adjList[cur->end].v.code_name << ", the weight is " << cur->weight
           << endl;
      cur = cur->next;
    }
  }
  cout << "There are " << vertex_num << "  vertices and " << arc_num << " edges"
       << endl;
}

void Map::AddArcNode(VNode &vNode, ArcNode &arc) {
  Edge newArc = new ArcNode;
  *newArc = arc;
  newArc->weight = 1;
  newArc->next = nullptr;
  if (vNode.firstArc == nullptr) {
    vNode.firstArc = vNode.lastArc = newArc;
  } else {
    vNode.lastArc->next = newArc;
    vNode.lastArc = newArc;
  }
}

Map::~Map() {
  Edge cur;
  Edge tmp;
  for (int i = 0; i < vertex_num; i++) {
    cur = adjList[i].firstArc;
    while (cur != nullptr) {
      tmp = cur->next;
      delete cur;
      cur = tmp;
    }
  }
}

Map::Map() {
  vertex_num = arc_num = 0;
  // 初始化邻接表表头
  for (int i = 0; i < MAX_V; i++) {
    adjList[i].firstArc = adjList[i].lastArc = nullptr;
  }
}
