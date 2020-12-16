#ifndef _BI_TREE_H_
#define _BI_TREE_H_
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

typedef struct trnode
{
    string expression; //存储表达式
    trnode *left;
    trnode *right;
} * PtrTrnode;

typedef struct tree
{
    PtrTrnode root;
    int size;
} * Tree;

/*
和树相关函数
*/
// 从文件读取信息并创建二叉树
void Read(Tree &tr);
// 创建一棵树
Tree CreateTree();
// 遍历树,借助队列层序遍历
void TraversalTree(PtrTrnode &root);
// 销毁树（递归方法）
void DisPoseTree(PtrTrnode root);
// 创建一个树节点
PtrTrnode MakeNode(string &);
// 后缀转换成表达式树
PtrTrnode PostfixToExpression(string &postfix);
// 根据表达式树进行计算（递归方法）
double Compute(Tree &root);

/*
与树不相关函数
*/

//主要的步骤，包括前缀转后缀，后缀转表达式树，利用表达式计算
void Manipulate(PtrTrnode &node);
// 判断是否为操作符
bool IsOperators(char &ch);
// 计算并返回结果
double results(string &expression, double a, double b);
// 判断是+，-还是*，/
bool IsAddOrSub(char &);
// 中缀转后缀
string InfixToPostfix(string &nifix);
//生成统计文件
void Write(int errorEx, int rightEx, double duration);
#endif