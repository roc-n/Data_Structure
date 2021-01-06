#ifndef _TEACHINGPLAN_
#define _TEACHINGPLAN_
#include "EntryTable.h"
#include "Map.h"
#include <set>
#include <vector>
using std::set;
using std::vector;
class Plan {
private:
  // 学期数,每学期的学分上限,课程数
  int terms, limit_per, courses;
  // 存储每个学期要修的课程
  vector<int> *arr;
  // 先修课程
  int first_class;
  // 存储各个课程的信息与关系
  Map map;
  Table *table;
  // 存储各课程的拓扑关系
  int *top_arr;

public:
  Plan();
  ~Plan();
  void Average_Strategy();
  void Gather_Strategy();
  void ReadInfo();
  void Calculate_Max(vector<int> &courses, int &credits, set<int> &store);
};

#endif
