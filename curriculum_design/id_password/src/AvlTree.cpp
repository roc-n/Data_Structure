#include "../include/AvlTree.h"
#include "../include/Sort.h"
static int Height(position P) {
  if (P == nullptr) {
    return -1;
  } else {
    return P->height;
  }
}

static int Max(int left, int right) {
  if (left > right) {
    return left;
  } else {
    return right;
  }
}

static position SingleRotateWithLeft(position k2) {
  position k1;
  k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;

  k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
  k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
  return k1;
}
static position SingleRotateWithRight(position k1) {
  position k2;
  k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;

  k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
  k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
  return k2;
}
static position DoubleRotateWithLeft(position k3) {
  k3->left = SingleRotateWithRight(k3->left);
  return SingleRotateWithLeft(k3);
}
static position DoubleRotateWithRight(position k1) {
  k1->right = SingleRotateWithLeft(k1->right);
  return SingleRotateWithRight(k1);
}
avlTree Insert(Item &item, avlTree T) {
  ptrToItem p_new, p_T;
  if (T == nullptr) {
    T = new avlNode;
    T->height = 0;
    T->left = T->right = nullptr;
    T->item = item;
  } else {
    p_new = &item;
    p_T = &T->item;
    if (LessThan(p_new, p_T)) {
      T->left = Insert(item, T->left);
      if (Height(T->left) - Height(T->right) == 2) {
        if (LessThan(p_new, p_T))
          T = SingleRotateWithLeft(T);
        else
          T = DoubleRotateWithLeft(T);
      }
    } else if (MoreThan(p_new, p_T)) {
      T->right = Insert(item, T->right);
      if (Height(T->right) - Height(T->left) == 2) {
        if (MoreThan(p_new, p_T)) {
          T = SingleRotateWithRight(T);
        } else {
          T = DoubleRotateWithRight(T);
        }
      }
    }
  }
  T->height = Max(Height(T->left), Height(T->right)) + 1;
  return T;
}
void MakeEMpty(avlTree T) {
  if (T == nullptr) {
    return;
  }
  MakeEMpty(T->left);
  MakeEMpty(T->right);
  delete T;
}
position FindMin(avlTree T) {
  if (T == nullptr) {
    return nullptr;
  } else if (T->left == nullptr) {
    return T;
  } else
    return FindMin(T->left);
}
position FindMax(avlTree T) {
  if (T == nullptr) {
    return nullptr;
  } else if (T->right == nullptr) {
    return T;
  } else
    return FindMax(T->right);
}
ptrToItem Find(int x, avlTree T) {
  if (T == nullptr) {
    return nullptr;
  }

  if (x < T->item.num) {
    return Find(x, T->left);
  } else if (x > T->item.num) {
    return Find(x, T->right);
  } else {
    return &T->item;
  }
}
