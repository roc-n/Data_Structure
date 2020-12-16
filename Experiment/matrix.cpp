#include <iostream>
using namespace std;
// 矩阵相加:相同位置处的元素相加
void Add_matrix(int row[], int column[], int &sum, int n) {
  sum = row[n] + column[n];
}
// 矩阵相乘:矩阵的行与列各元素相乘再相加
void Multiply_matrix(int row[], int column[], int &sum, int n) {
  sum = 0;
  for (int i = 0; i < n; i++)
    sum += row[i] * column[i];
}
// 展示矩阵
void Display(int matrix[][4], int row, int column) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
  cout << "###################" << endl;
}
// 遍历矩阵并执行不同的操作,通过传入的函数指针实现
void Traversal(int matrix1[][4], int matrix2[][4], int matrix3[][4], int row,
               int column, void (*pf)(int[], int[], int &, int),
               bool check = true) {
  int col[4]; //暂时存储矩阵B的列
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      if (check) {
        (*pf)(matrix1[i], matrix2[i], matrix3[i][j], j);
      } else {
        for (int cnt = 0; cnt < 4; cnt++)
          col[cnt] = matrix2[cnt][i];
        (*pf)(matrix1[i], col, matrix3[i][j], 4);
      }
    }
  }
}

int main(void) {
  // 初始化4✖4矩阵
  int matrix_A[4][4] = {{1, 1, 2, 4}, {1, 2, 3, 5}, {2, 3, 4, 6}, {4, 5, 6, 7}};
  int matrix_B[4][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
  int a[6];
  int b[6];
  int cnt_a = 0;
  int cnt_b = 0;
  int matrix_C[4][4];
  int matrix_D[4][4];
  // 找出矩阵中下三角元素
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i > j) { //判断的关键,所有下三角元素均满足i>j
        b[cnt_a++] = matrix_B[i][j];
        a[cnt_b++] = matrix_A[i][j];
      }
    }
  }
  for (int i = 0; i < cnt_a; i++) {
    cout << a[i] << "	";
  }
  cout << endl;
  for (int j = 0; j < cnt_b; j++) {
    cout << b[j] << "	";
  }
  cout << endl;
  // 矩阵相加与相乘
  Traversal(matrix_A, matrix_B, matrix_C, 4, 4, Multiply_matrix, false);
  Traversal(matrix_A, matrix_B, matrix_D, 4, 4, Add_matrix);
  Display(matrix_C, 4, 4);
  Display(matrix_D, 4, 4);
  return 0;
}
