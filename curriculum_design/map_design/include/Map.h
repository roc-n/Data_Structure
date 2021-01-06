#ifndef _CLASS_ADJLIST_MAP_
#define _CLASS_ADJLIST_MAP_
#include <map>
#include <string>

using std::map;
using std::string;
#define MAX_V 50
// 顶点的结构
typedef struct {
  int num;
  int credit;
  string code_name;
  // InfoType info 顶点其他信息
} Vertex;
// 边的结构
typedef struct ArcNode {
  int end; //弧的终点
  ArcNode *next;
  int weight;
  // InfoType info    边的其他信息
} * Edge;
// 邻接表头节点类型
typedef struct vNode {
  Vertex v;
  Edge firstArc;
  Edge lastArc;
} VNode;

// 定义图类
class Map {
private:
  VNode adjList[MAX_V];
  int vertex_num, arc_num;
  // 构建顶点字符串与内部数字的联系
  map<string, int> hash;

public:
  Map();
  ~Map();
  // 添加边节点
  void AddArcNode(VNode &vNode, ArcNode &arc);
  //从文件读取信息并设置参数
  void Read();
  // 展现图
  void Display_edge();

  friend void TopSort(Map &map, int top_arr[]);
  friend void Get_Indegree(Map &map, int arr[]);
  friend class Table;
  friend class Plan;
};
void DisplaySort(int top_arr[], int n);
#endif