#ifndef _MAP_ADJMATRIX_H_
#define _MAP_ADJMATRIX_H_
#define MAX_V 50
namespace Matrix {
// 点的结构，含标号
typedef struct {
  int num;
  // InfoType info 顶点其他信息
} Vertex;
// 边的结构，含两端点
typedef struct {
  int v1;
  int v2;
} Edge;
// 定义图结构
typedef struct {
  int edges[MAX_V][MAX_V]; //采用邻接矩阵存储边
  int vertex_num, arc_num;
  Vertex vex[MAX_V];
} Graph;
//初始化图
void Init(Graph &map);
//从文件读取信息并设置参数
void Read(Graph &map);
// 展现图的边
void Display_edge(Graph &map);
}
#endif
