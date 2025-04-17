#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

struct LCSResult {
    int length;
    string sequence;
};

LCSResult f(int m, int n, char s1[], char s2[]) {  // 修改参数类型为char数组 [[19]]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // 动态规划填表
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 回溯查找LCS序列
    vector<char> lcs_chars;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs_chars.push_back(s1[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    reverse(lcs_chars.begin(), lcs_chars.end());
    string sequence;
    for (char ch : lcs_chars) {
        sequence += ch;
        sequence += " ";
    }
    if (!sequence.empty()) {  //sequence.empty()是一个布尔型的函数，这里是先判断刚才的字符串为不为空，不为空才去空格。
        sequence.pop_back();  // 移除末尾空格 [[12]]
    }
    
    return {dp[m][n], sequence};
}

int main() {
    int m, n;
    cout << "请输入第一个数组的长度" << endl;
    cin >> m;
    cout << "请输入第二个数组的长度" << endl;
    cin >> n;
    cin.ignore();  // 清除输入缓冲区 [[16]]
    
    vector<char> s1(m), s2(n);
    
    cout << "请输入第一个数组（元素间用空格分隔）" << endl;
    for (int i = 0; i < m; i++) {
        cin >> s1[i];  // 直接读取字符 [[19]]
    }
    
    cout << "请输入第二个数组（元素间用空格分隔）" << endl;
    for (int i = 0; i < n; i++) {
        cin >> s2[i];
    }
    
    LCSResult result = f(m, n, s1.data(), s2.data());
    cout << "最长公共子序列的长度为：" << result.length << endl;
    cout << "其中一个最长公共子序列是：" << result.sequence << endl;
    
    return 0;
}
