#ifndef _ENTRYTABLE_
#define _ENTRYTABLE_
#define NullVertex -1
#define Infinity -1
#define ZEROS -1
typedef int vertex;
#include "Map.h"
// 动态表中每个顶点需要存储的信息
typedef struct TableEntryUnit {
  VNode head;
  vertex path;
  bool known;
  int credit;
  // int dist;
} * unitTable;

class Table {
private:
  int vertex_num;
  unitTable *allTable;

public:
  Table(vertex start, Map &map);
  Table();
  void InitTable(vertex start, Map &map);
  void ReadGraph(Map &map);
  friend class Plan;
};
// 得到表中dist最小的未知顶点
vertex SmallestDist_Vertex(Table &T);
// 初始化表的子函数，将图的邻接表链接到表中
// 狄克斯特拉相关函数
void PrintPath(vertex v, Table &T);
int GetCost(vertex v, Table &T);
void Dijkstra(Table &T);
// 普利姆算法相关函数
void Prime(Table &T);
void Display(Table &T);
#endif
