#include<iostream>
#include<climits>
#include<cmath>
#include<ctime>
#include<vector> // 添加了vector头文件
using namespace std;

void printChain(int i, int j, const vector<vector<int>>& s, int n) { // 修改参数类型为vector
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printChain(i, s[i][j], s, n);
        printChain(s[i][j] + 1, j, s, n);
        cout << ")";
    }
}

void MATRIX_CHAIN_ORDER(int p[], int n) {
    // 使用vector代替动态分配的二维数组
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    int i, j, k, L, q;

    for (i = 1; i <= n; i++)
        m[i][i] = 0;
    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k < j; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    cout << "最少标量乘法次数：" << m[1][n] << endl;
    cout << "最优乘法顺序：";
    printChain(1, n, s, n);
    cout << endl;
}

int main() {
    srand(time(0));
    int p[] = {2, 3, 6, 4, 2, 7};
    int n = sizeof(p) / sizeof(p[0]) - 1;
    cout << "n=" << n << "时矩阵链规模：";
    for (int i = 0;i < n + 1;i++) {
        cout << p[i] << " ";
    }
    cout << endl;
    MATRIX_CHAIN_ORDER(p, n);

    cout << endl << "n=50时矩阵链规模：";
    n = 50;
    vector<int> p1(n + 1); // 使用vector存储矩阵链规模
    for (int i = 0; i <= n; i++) {
        p1[i] = rand() % 9 + 1;
        cout << p1[i] << " ";
    }
    cout << endl;
    MATRIX_CHAIN_ORDER(p1.data(), n); // 传递vector的data指针

    cout << endl << "n=100时矩阵链规模：";
    n = 100;
    vector<int> p2(n + 1);
    for (int i = 0; i <= n; i++) {
        p2[i] = rand() % 9 + 1;
        cout << p2[i] << " ";
    }
    cout << endl;
    MATRIX_CHAIN_ORDER(p2.data(), n);
}