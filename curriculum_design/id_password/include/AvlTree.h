#ifndef _AVLTREE_
#define _AVLTREE_
#include "../include/User.h"
struct avlNode;
typedef struct avlNode *position;
typedef struct avlNode *avlTree;

struct avlNode {
  Item item;
  avlTree left;
  avlTree right;
  int height;
};

void MakeEMpty(avlTree T);
ptrToItem Find(int x, avlTree T);
position FindMin(avlTree T);
position FindMax(avlTree T);
avlTree Insert(Item &item, avlTree T);
#endif