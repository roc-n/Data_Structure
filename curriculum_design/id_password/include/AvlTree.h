/*
  avl树的声明，包含构建，查找，清空的功能
*/

#ifndef _AVLTREE_
#define _AVLTREE_
#include "../include/User.h"
struct avlNode;
typedef struct avlNode *position;
typedef struct avlNode *avlTree;

// 树的节点,存储左右节点与高度及数据
struct avlNode {
  Item item;
  avlTree left;
  avlTree right;
  int height;
};

// 清空树
void MakeEMpty(avlTree T);
// 查找数据
ptrToItem Find(int x, avlTree T);
// 查找最小值
position FindMin(avlTree T);
// 查找最大值
position FindMax(avlTree T);
// 添加新节点
avlTree Insert(Item &item, avlTree T);
#endif