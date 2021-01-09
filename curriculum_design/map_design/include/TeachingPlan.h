#ifndef _TEACHINGPLAN_
#define _TEACHINGPLAN_
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
  vector<int> first_class;
  // 存储各个课程的信息与关系
  Map map;
  //存储各课程的入度
  vector<int> indegree;
  // 未修课程
  set<int> un_courses;
  // 平均值
  int average;

public:
  Plan();
  ~Plan();
  // 得到每个顶点的入度
  void GetIndegree(Map &map);
  // 采取平均策略
  void Average_Strategy();
  // 采取贪婪策略
  void Gather_Strategy();
  // 获取学期数与每学期学分上限
  void ReadInfo();
  // 更新入度
  void UpdateInderee(vector<int> &indegree, int vertex);
  // 递归计算一个学期所能学习的最多课程
  void Calculate_Max(vector<int> &courses, int &credits,
                     set<int> &one_term_courses, vector<int> &indegree);
  void Calculate_Average(vector<int> &courses, int &credits,
                         set<int> &one_term_courses, vector<int> &indegree);
  // 选择以哪种策略进行规划
  void PlanStrategy();
  // 展示结果
  void Display();
};

#endif
