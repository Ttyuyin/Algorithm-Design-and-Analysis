#include<iostream>
#include <limits.h>
using namespace std;
#define N 5

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

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            D[i][j] = W[i][j];
        }
    }
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

    printMatrix(D, 0);
    printPiMatrix(Pi, 0);

    for (int k = 0; k < N; ++k) {
        int D_new[N][N];
        int Pi_new[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                D_new[i][j] = D[i][j];
                Pi_new[i][j] = Pi[i][j];
            }
        }
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
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                D[i][j] = D_new[i][j];
                Pi[i][j] = Pi_new[i][j];
            }
        }

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