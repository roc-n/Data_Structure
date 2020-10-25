#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

/*声明与定义*/
#define max 100

//定义顺序表结构
typedef struct list
{
    int size;
    int arr[max];
} liner, *List;

void Add(int &a, List &list);      //添加数据到顺序表
bool IsEmpty(List &list);          //判断是否为空
bool IsFull(List &list);           //判断是否为满
List &CreateList(List &list);      //创建一个顺序表
int Find(List &list, int &num);    //查找指定元素，找到则返回下标值
void Change(List &list, int &pos); //查找后将查找元素调至表头
void MakeEmpty(List &list);        //清空顺序表
void DisposeList(List &list);      //销毁顺序表
void Copy(List &list);             //头插法的操作

/*测试程序*/
int main(void)
{
    List l = CreateList(l);
    for (int i = 0; i < max; i++)
        Add(i, l);
    int check = 2;
    Find(l, check);
    Find(l, check);
    check = 3;
    Find(l, check);
    check = 100;
    Find(l, check);
    DisposeList(l);
    return 0;
}

/*实现*/
List &CreateList(List &list)
{
    list = (List)malloc(sizeof(liner));
    list->size = 0;
    return list;
}
void Add(int &a, List &list)
{
    //异常处理机制
    if (IsFull(list))
    {
        cout << "The list is full!" << endl;
        return;
    }
    Copy(list); //头插
    list->arr[0] = a;
    list->size++;
}

void Copy(List &list)
{
    for (int i = list->size; i > 0; i--) //从后往前遍历
    {
        list->arr[i] = list->arr[i - 1];
    }
}

void MakeEmpty(List &list)
{
    list->size = 0;
}

void DisposeList(List &list)
{
    free(list); //释放内存
}
bool IsFull(List &list)
{
    return list->size == max;
}

bool IsEmpty(List &list)
{
    return list->size == 0;
}

int Find(List &list, int &num)
{
    if (IsEmpty(list))
    {
        cout << "The list is Empty!" << endl;
        return -1;
    }
    int *point = find(list->arr, list->arr + list->size, num); //使用<algorithm>库中的find查找函数，返回指针
    if (point != list->arr + list->size)
    {
        int pos = (point - list->arr); //存储下标
        cout << "The num is at " << pos << " index" << endl;
        Change(list, pos);
        return pos;
    }
    else
    {
        cout << "Not find." << endl;
        return -1;
    }
}

void Change(List &list, int &pos)
{
    int tmp = list->arr[pos]; //暂时存储查找得到的数据
    for (int i = pos; i > 0; i--)
    {
        list->arr[i] = list->arr[i - 1]; //将第二个数据全部往后挪一位直至到达pos下标处
    }
    list->arr[0] = tmp;
}
