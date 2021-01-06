#include "../include/TeachingPlan.h"
#include "../include/Map.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <set>

static void Calculate_Combination(int n, vector<Vertex> q,
                                  vector<Vertex> store) {}

using namespace std;
Plan::Plan() {
  void ReadInfo();
  courses = map.vertex_num;
  arr = new vector<int>[terms];
  top_arr = new int[terms];
  TopSort(map, top_arr);
  table = new Table(terms, map);
}

Plan::~Plan() {
  delete[] arr;
  delete[] top_arr;
};

void Plan::ReadInfo() {
  cout << "Enter the semesters:" << endl;
  cin >> terms;
  cout << "Enter the credit limit per semester:" << endl;
  cin >> limit_per;
}

void Plan::Gather_Strategy() {
  int sum = 0;
  set<int> v;
  for (int i = 0; i < terms; i++) {
    int course = first_class;
    while (1) {
      sum += table->allTable[first_class]->head.v.credit;
      queue<Vertex> q;
      Vertex tmp;
      if (sum <= limit_per) {
        Edge cur = table->allTable[course]->head.firstArc;
        while (cur != nullptr) {
          // table->allTable[cur->end]->known = true;
          if (sum + map.adjList[cur->end].v.credit <= limit_per) {
            q.push(map.adjList[cur->end].v);
          }
          cur = cur->next;
        }

        tmp = q.back();
        sum += tmp.credit;
      } else {
      }
      course =
    }

    // arr[i].push_back()
  }
}
// 递归计算一个学期所能学习的最多课程
void Plan::Calculate_Max(vector<int> &courses, int &credits, set<int> &store) {
  for (int i = 0; i < courses.size(); ++i) {
    if (credits + map.adjList[courses[i]].v.credit <= limit_per) {
      credits += map.adjList[courses[i]].v.credit;
      store.insert(courses[i]);
    } else {
      return;
    }
  }

  vector<Vertex> v;
  Vertex tmp;
  int course;
  Edge cur;
  for (int i = 0; i < courses.size(); ++i) {
    if (credits <= limit_per) {
      cur = table->allTable[course]->head.firstArc;
      while (cur != nullptr) {
        // table->allTable[cur->end]->known = true;
        if (credits + map.adjList[cur->end].v.credit <= limit_per) {
          v.push_back(map.adjList[cur->end].v);
          // if (credits + map.adjList[cur->end].v.credit > credits) {
          //   credits += map.adjList[cur->end].v.credit;
          // }
        }
        cur = cur->next;
      }
    }
  }
  for (int i = 0; i < v.size(); ++i) {
    for (;;) {
    }
    Calculate_Max(courses, credits);
  }
}