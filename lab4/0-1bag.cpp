#include <iostream>
#include <vector>
using namespace std;

int main() {
    //
    // 输入物品数量和背包容量
    int n, W;
    cout << "请输入物品数量: ";
    cin >> n;
    cout << "请输入背包容量: ";
    cin >> W;

    // 输入每个物品的重量和价值
    vector<int> weight(n), value(n);
    cout << "请输入每个物品的重量（共" << n << "个）: ";
    for (int i = 0; i < n; i++) cin >> weight[i];
    
    cout << "请输入每个物品的价值（共" << n << "个）: ";
    for (int i = 0; i < n; i++) cin >> value[i];

    // DP表：dp[i][j]表示前i个物品在容量j时的最大价值
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // 填充DP表
    for (int i = 1; i <= n; i++) {          // i代表前i个物品
        for (int j = 1; j <= W; j++) {      // j代表当前背包容量
            if (weight[i - 1] > j) {         // 如果当前物品太重，不能选
                dp[i][j] = dp[i - 1][j];     // 不选它，继承前i-1个物品的最优解
            } else {                         // 否则可以选或不选
                // max(不选当前物品的价值, 选当前物品的价值 + 剩余容量的最优解)
                dp[i][j] = max(dp[i - 1][j], value[i - 1] + dp[i - 1][j - weight[i - 1]]);
            }
        }
    }

    // 输出DP表（便于理解）
    cout << "\nDP表：" << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    // 输出最大价值
    cout << "\n最大价值: " << dp[n][W] << endl;

    // **找出被选中的物品**
    //01背包的回溯，要看最大值，以及与头上的那个是否相等，如果相等，就是本行的物品被选了，进行上一行看，同时重量要减去刚才的重量。
    //如果不相等，则是说明本行的那个要选上，同时也要进行回溯上一行。
    vector<bool> selected(n, false); // selected[i]=true表示第i个物品被选中
    int i = n, j = W;
    
    while (i > 0 && j > 0) {
        if (dp[i][j] != dp[i - 1][j]) { // 说明选了第i个物品
            selected[i - 1] = true;      // selected数组从0开始，所以是i-1
            j -= weight[i - 1];          // 减去当前物品的重量
        }
        i--;                            // 继续检查前一个物品
    }

    // **输出被选中的物品**
    cout << "\n被选中的物品：" << endl;
    for (int k = 0; k < n; k++) {
        if (selected[k]) {
            cout << "物品" << k + 1 
                 << "（重量：" << weight[k] 
                 << ", 价值：" << value[k] 
                 << "）" << endl;
        }
    }

    return 0;
}
