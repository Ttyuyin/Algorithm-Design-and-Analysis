#include<iostream>
#include <limits.h>
using namespace std;
#define N 5

//打印矩阵
void printMatrix(int matrix[N][N], int n) {
    cout << "D^(" << n << ")=" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] == INT_MAX) {
                printf(" INF ");
            }
            else {
                printf("%4d ", matrix[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
}
//打印Pi矩阵
void printPiMatrix(int piMatrix[N][N], int n) {
    cout << "Pi^(" << n << ")=" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (piMatrix[i][j] == -1) {
                printf(" NIL ");
            }
            else {
                printf("%4d ", piMatrix[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void floydWarshall(int W[N][N]) {
    int D[N][N];
    int Pi[N][N];

    //第一个D[0][0]和原矩阵W[N][N]是相等的
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            D[i][j] = W[i][j];
        }
    }
    //求Pi矩阵。if条件里面是，自己不能是自己的前驱节点。同时不能无法到达
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j && D[i][j] != INT_MAX) {
                Pi[i][j] = i + 1;
            }
            else {
                Pi[i][j] = -1;
            }
        }
    }

    //把第0矩阵打印出来
    printMatrix(D, 0);
    printPiMatrix(Pi, 0);

    for (int k = 0; k < N; ++k) {
        //生成一个新的操作矩阵
        int D_new[N][N];
        int Pi_new[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                D_new[i][j] = D[i][j];
                Pi_new[i][j] = Pi[i][j];
            }
        }
        //循环赋值与更新
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX) {
                    if (D[i][j] > D[i][k] + D[k][j]) {
                        D_new[i][j] = D[i][k] + D[k][j];
                        Pi_new[i][j] = Pi[k][j];
                    }
                }
            }
        }
        //赋值回去
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                D[i][j] = D_new[i][j];
                Pi[i][j] = Pi_new[i][j];
            }
        }
        //打印k的取值是0到N-1，第0个已经打印，所以现在要打印1到N的
        printMatrix(D, k + 1);
        printPiMatrix(Pi, k + 1);
    }
}

int main() {
    int W[N][N] = {
        {0, 3, 8, INT_MAX, -4},
        {INT_MAX, 0, INT_MAX, 1, 7},
        {INT_MAX, 4, 0, INT_MAX, INT_MAX},
        {2, INT_MAX, -5, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 6, 0}
    };

    floydWarshall(W);
    return 0;
}
