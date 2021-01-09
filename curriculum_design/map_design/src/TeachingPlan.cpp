#include "../include/TeachingPlan.h"
#include "../include/Map.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <queue>
#include <set>

using namespace std;

bool EndCount(unique_ptr<int[]> &pointers, int step, int n) {
  for (int i = 0; i < n; ++i) {
    if (pointers[i] != i + step) {
      return true; //指针没有全部到达尾部,组合计数继续
    }
  }
  return false; //到达尾部,组合计数停止
}

// n为每个组合中元素的个数,v是总共的元素集,store存储每个组合的结果
static void Calculate_Combination(int n, const vector<int> &v,
                                  vector<int> &store) {
  unique_ptr<int[]> pointers(new int[v.size()]);
  //  指针最大步长
  int step = v.size() - n + 1;
  for (int i = 0; i < n; ++i) {
    pointers[i] = i;
  }

  while (EndCount(pointers, step, n)) {
    for (int i = 0; i < n; i++) {
      store.push_back(v[pointers[i]]);
    }
    //每添加一个组合就让最后面的指针步进一
    pointers[n - 1]++;
    //检测各指针是否到达最后位置,若到达则更新指针位置
    for (int i = n - 1; i > 0; --i) {
      if (pointers[i] == i + step) {
        pointers[i - 1]++;
        for (int j = i; j < n; j++) {
          pointers[j] = pointers[j - 1] + 1;
        }
      }
    }
  }
}

void Plan::UpdateInderee(vector<int> &indegree, int vertex) {
  Edge cur = map.adjList[vertex].firstArc;
  while (cur) {
    indegree[cur->end]--;
    cur = cur->next;
  }
}

Plan::Plan() {
  ReadInfo();
  courses = map.vertex_num;
  arr = new vector<int>[terms];
  GetIndegree(map);
  average = 0;
  for (int i = 0; i < this->courses; ++i) {
    un_courses.insert(i);
  }
  // top_arr = new int[terms];
  // TopSort(map, top_arr);
  // table = new Table(terms, map);
}

Plan::~Plan() { delete[] arr; };

void Plan::ReadInfo() {
  cout << "Enter the semesters:" << endl;
  cin >> terms;
  cout << "Enter the credit limit per semester:" << endl;
  cin >> limit_per;
  cout << "Enter the first courses(course code name,\"end\" to terminate):"
       << endl;
  string tmp;
  int course;
  cin >> tmp;
  while (tmp != "end") {
    course = map.hash[tmp];
    first_class.push_back(course);
    cin >> tmp;
  }
}

void Plan::Gather_Strategy() {
  // 一个学期所修的课程
  set<int> one_term_courses;
  // 每学期起始课程
  vector<int> courses;
  // 每学期修的学分
  int credit;
  // 迭代器
  set<int>::iterator itor;
  courses = first_class;
  for (int i = 0; i < terms; i++) {
    Calculate_Max(courses, credit, one_term_courses, indegree);
    for (itor = one_term_courses.begin(); itor != one_term_courses.end();
         ++itor) {
      arr[i].push_back(*itor);
      un_courses.erase(*itor);
    }
    // for (int j = 0; j < arr[i].size(); ++j) {
    //   cout << arr[i][j] << endl;
    // }
    one_term_courses.clear();
    courses.clear();

    for (itor = un_courses.begin(); itor != un_courses.end(); ++itor) {
      if (indegree[*itor] == 0) {
        courses.push_back(*itor);
      }
    }
    credit = 0;
  }
}

void Plan::Average_Strategy() {
  for (int i = 0; i < terms; ++i) {
    average += map.adjList[i].v.credit;
  }
  average /= terms;

  // 一个学期所修的课程
  set<int> one_term_courses;
  // 每学期起始课程
  vector<int> courses;
  // 每学期修的学分
  int credit;
  // 迭代器
  set<int>::iterator itor;
  courses = first_class;
  for (int i = 0; i < terms; i++) {
    Calculate_Average(courses, credit, one_term_courses, indegree);
    for (itor = one_term_courses.begin(); itor != one_term_courses.end();
         ++itor) {
      arr[i].push_back(*itor);
      un_courses.erase(*itor);
    }
    // for (int j = 0; j < arr[i].size(); ++j) {
    //   cout << arr[i][j] << endl;
    // }
    one_term_courses.clear();
    courses.clear();

    for (itor = un_courses.begin(); itor != un_courses.end(); ++itor) {
      if (indegree[*itor] == 0) {
        courses.push_back(*itor);
      }
    }
    credit = 0;
  }
}

// 递归计算一个学期所能学习的最多课程
void Plan::Calculate_Max(vector<int> &courses, int &credits,
                         set<int> &one_term_courses, vector<int> &indegree) {
  // 添加学分并存储顶点
  for (int i = 0; i < courses.size(); ++i) {
    if (credits + map.adjList[courses[i]].v.credit <= limit_per) {
      credits += map.adjList[courses[i]].v.credit;
      one_term_courses.insert(courses[i]);
      UpdateInderee(indegree, courses[i]);
    } else {
      return;
    }
  }
  // 存储被点亮的顶点
  vector<int> v;
  // 迭代
  Edge cur;
  // 将传进来的顶点指向的且符合拓扑逻辑的顶点逐个点亮
  for (int i = 0; i < courses.size(); ++i) {
    cur = map.adjList[courses[i]].firstArc;
    while (cur != nullptr) {
      // 判断入度是否为0
      if (indegree[cur->end] == 0) {
        v.push_back(cur->end);
      }
      cur = cur->next;
    }
  }
  //  存储所有组合中的元素，组合之间没重合，元素之间有重合
  vector<int> store_arr;
  //  要传入递归函数的子顶点
  vector<int> sub_courses;

  // 组合数
  int C = 0;
  set<int> last_set = one_term_courses;
  int last_credits = credits;
  vector<int> last_indegree = indegree;

  // 计算n为不同值情况下各组合情况
  int j = 1;
  int size = v.size();

  while (j <= size) {
    cout << v.size();
    Calculate_Combination(j, v, store_arr);
    cout << v.size() << endl;
    C = store_arr.size() / j;
    // 建立当前位置副本，数量与计算到的组合数相等，想象成支线，每条线都要走一遍
    int *sub_credits = new int[C];
    set<int> *sub_set = new set<int>[C];
    vector<int> *sub_indegree = (vector<int> *)new vector<int>[C];
    // 初始化副本
    for (int i = 0; i < C; ++i) {
      sub_credits[i] = credits;
      sub_set[i] = one_term_courses;
      sub_indegree[i] = indegree;
    }
    // 将当前组合全部走一遍
    for (int k = 0, count = 0; k < store_arr.size(); k++) {
      sub_courses.push_back(store_arr[k]);
      if (sub_courses.size() % j == 0) {
        Calculate_Max(sub_courses, sub_credits[count], sub_set[count],
                      sub_indegree[count]);
        //更新学分与本学期课程
        if (sub_credits[count] > last_credits) {
          last_credits = sub_credits[count];
          last_set = sub_set[count];
          last_indegree = sub_indegree[count];
        }
        // 走完一条路径后换用另一套副本
        count++;
        sub_courses.clear();
      }
    }
    j = j + 1;

    store_arr.clear();
    delete[] sub_credits;
    delete[] sub_set;
    delete[] sub_indegree;
  }

  credits = last_credits;
  one_term_courses = last_set;
  indegree = last_indegree;
}

void Plan::GetIndegree(Map &map) {
  for (int i = 0; i < map.vertex_num; i++) {
    indegree.push_back(0);
  }

  Edge cur;
  for (int i = 0; i < map.vertex_num; i++) {
    cur = map.adjList[i].firstArc;
    while (cur != nullptr) {
      indegree[cur->end]++;
      cur = cur->next;
    }
  }
}

void Plan::Display() {
  for (int i = 0; i < terms; ++i) {
    cout << "The " << i + 1 << " semester include this courses:" << endl;
    for (int j = 0; j < arr[i].size(); ++j) {
      cout << map.adjList[arr[i][j]].v.code_name << "\t";
    }
    cout << endl;
  }
}

void Plan::PlanStrategy() {
  cout << "Choose one to plan:" << endl;
  cout << "\"a\" average.\n"
       << "\"b\" greedy" << endl;
  string choose;
  cin >> choose;
  if (choose == "a") {
    Average_Strategy();
  } else if (choose == "b") {
    Gather_Strategy();

  } else {
    cout << "Input Error." << endl;
  }
}

void Plan::Calculate_Average(vector<int> &courses, int &credits,
                             set<int> &one_term_courses,
                             vector<int> &indegree) {
  // 添加学分并存储顶点
  for (int i = 0; i < courses.size(); ++i) {
    if (credits + map.adjList[courses[i]].v.credit <= limit_per) {
      credits += map.adjList[courses[i]].v.credit;
      one_term_courses.insert(courses[i]);
      UpdateInderee(indegree, courses[i]);
    } else {
      return;
    }
  }
  // 存储被点亮的顶点
  vector<int> v;
  // 迭代
  Edge cur;
  // 将传进来的顶点指向的且符合拓扑逻辑的顶点逐个点亮
  for (int i = 0; i < courses.size(); ++i) {
    cur = map.adjList[courses[i]].firstArc;
    while (cur != nullptr) {
      if (indegree[courses[i]] == 0) {
        v.push_back(cur->end);
      }
      cur = cur->next;
    }
  }
  //  存储所有组合中的元素，组合之间没重合，元素之间有重合
  vector<int> store_arr;
  //  要传入递归函数的子顶点
  vector<int> sub_courses;

  // 组合数
  int C = 0;
  set<int> last_set = one_term_courses;
  int last_credits = credits;
  vector<int> last_indegree = indegree;

  // 计算n为不同值情况下各组合情况
  for (int j = 1; j <= v.size(); j++) {
    Calculate_Combination(j, v, store_arr);
    C = store_arr.size() / j;
    // 建立当前位置副本，数量与计算到的组合数相等，想象成支线，每条线都要走一遍
    int *sub_credits = new int[C];
    set<int> *sub_set = new set<int>[C];
    vector<int> *sub_indegree = (vector<int> *)new vector<int>[C];
    for (int i = 0; i < C; ++i) {
      sub_credits[i] = credits;
      sub_set[i] = one_term_courses;
      sub_indegree[i] = indegree;
    }

    for (int k = 0, count = 0; k < store_arr.size(); k++) {
      sub_courses.push_back(store_arr[k]);
      if (sub_courses.size() % j == 0) {
        Calculate_Average(sub_courses, sub_credits[count], sub_set[count],
                          sub_indegree[count]);
        //更新学分与本学期课程
        if (abs(sub_credits[count] - average) < abs(last_credits - average)) {
          last_credits = sub_credits[count];
          last_set = sub_set[count];
          last_indegree = sub_indegree[count];
        }
        // 走完一条路径后换另一条路径
        count++;
        sub_courses.clear();
      }
    }
    store_arr.clear();
    delete[] sub_credits;
    delete[] sub_set;
    delete[] sub_indegree;
  }
  credits = last_credits;
  one_term_courses = last_set;
  indegree = last_indegree;
}