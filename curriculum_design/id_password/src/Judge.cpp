#include "../include/Sort.h"
bool LessThan(ptrToItem &left, ptrToItem &right) {
  return left->num < right->num;
}
bool MoreThan(ptrToItem &left, ptrToItem &right) {
  return left->num > right->num;
}
bool Equal(ptrToItem &left, ptrToItem &right) {
  return left->num == right->num;
}
bool Less_EqualThan(ptrToItem &left, ptrToItem &right) {
  return left->num <= right->num;
}
bool More_EqualThan(ptrToItem &left, ptrToItem &right) {
  return left->num >= right->num;
}