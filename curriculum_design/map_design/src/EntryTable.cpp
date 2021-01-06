#include "../include/EntryTable.h"
#include <iostream>
using namespace std;

// 初始化表，将表中每个顶点的path与known,credit均置默认值
Table::Table(vertex start, Map &map) {
  allTable = (unitTable *)malloc(sizeof(unitTable) * map.vertex_num);
  vertex_num = map.vertex_num;
  for (int i = 0; i < vertex_num; i++) {
    allTable[i]->known = false;
    allTable[i]->credit = Infinity;
    allTable[i]->path = NullVertex;
  }
  allTable[start]->credit = 0;
  ReadGraph(map);
}

void Table::InitTable(vertex start, Map &map) {}

// 递归输出到某点的最短路径
// void PrintPath(vertex v, Table &T) {
//   if (T.allTable[v]->path != NullVertex) {
//     PrintPath(T.allTable[v]->path, T);
//     cout << " to ";
//   }
// }
// // cout << v;
// // }
// // 核心算法
// void Dijkstra(Table &T) {
//   vertex v, w;
//   // 主循环
//   while (1) {
//     v = SmallestDist_Vertex(T);
//     // 若所有点均已走过则计算完毕，退出
//     if (v == NullVertex) {
//       break;
//     }
//     T.allTable[v]->known = true;
//     // 将所有与v点邻近的点的path和dist更新
//     Edge cur = T.allTable[v]->head.firstArc;
//     while (cur != nullptr) {
//       w = cur->vertex;
//       if (!T.allTable[w]->known) {
//         if (T.allTable[w]->dist == Infinity ||
//             T.allTable[v]->dist + cur->weight < T.allTable[w]->dist) {
//           {
//             T.allTable[w]->dist = T.allTable[v]->dist + cur->weight;
//             T.allTable[w]->path = v;
//           }
//         }
//       }
//       cur = cur->next;
//     }
//   }
// }
// // // 得到对应点到起点的最短路径长度
// // int GetCost(vertex v, Table &T) { return T.allTable[v]->dist; }

// void Table::ReadGraph(Map &map) {
//   unitTable pT;
//   for (int i = 0; i < map.vertex_num; i++) {
//     pT = new TableEntryUnit;
//     pT->head = map.adjList[i];
//     allTable[i] = pT;
//   }
// }

// vertex MaxCredit_Vertex

//     vertex
//     SmallestDist_Vertex(Table &T) {
//   int min;
//   bool check = false;
//   vertex v = NullVertex;
//   for (int i = 0; i < T.vertex_num; i++) {
//     if (!T.allTable[i]->known && T.allTable[i]->dist != Infinity) {
//       if (!check || T.allTable[i]->dist < min) {
//         min = T.allTable[i]->dist;
//         v = i;
//         check = true;
//       }
//     }
//   }
//   return v;
// }