#ifndef _MAP_ADJLIST_H_
#define _MAP_ADJLIST_H_
#define MAX_V 50
// 点的结构，含标号
typedef struct {
  int num;
  int degree; //无向图的度
} Vertex;
// 边的结构
typedef struct ArcNode {
  int vertex; //弧的终点
  ArcNode *next;
  // InfoType info    弧的相关信息如权值
} * Edge;
// 邻接表头节点类型
typedef struct vNode {
  Vertex data;
  Edge firstArc;
  Edge lastArc;
} VNode;
// 定义图结构
typedef struct {
  VNode adjList[MAX_V];
  int vertex_num, arc_num;
} Graph;
//  初始化图
void Init(Graph &map);
//  从文件读取信息并设置参数
void Read(Graph &map);
//  展现图
void Display(Graph &map);
//  搜索路径
void SearchPath(Graph &map);
//  销毁申请的内存
void DisPose(Graph &map);
//  邻接表添加边节点
void AddNode(VNode &vNode, int vertex);
#endif