// 求最大和子数组算法实验：蛮力搜索、分治法、动态规划
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits.h>

#define N 100000

using namespace std;

struct MAXSUB {
    int low;
    int high;
    long sum;
};

MAXSUB EXHAUSTIONMAXSUBArray(const vector<int>& R) {
    MAXSUB m = {0, 0, R[0]};
    int n = R.size();
    for (int i = 0; i < n; i++) {
        long tempsum = 0;
        for (int j = i; j < n; j++) {
            tempsum += R[j];
            if (tempsum > m.sum) {
                m.sum = tempsum;
                m.low = i;
                m.high = j;
            }
        }
    }
    return m;
}

// 分治法
// 计算跨越中点的最大子数组
MAXSUB FINDMAXCROSSINGSUBARRAY(const vector<int>& R, int low, int mid, int high) {
    long leftsum = R[mid];
    long sum = leftsum;
    int maxleft = mid;
    for (int i = mid - 1; i >= low; i--) {
        sum += R[i];
        if (sum > leftsum) {
            leftsum = sum;
            maxleft = i;
        }
    }

    long rightsum = R[mid + 1];
    sum = rightsum;
    int maxright = mid + 1;
    for (int i = mid + 2; i <= high; i++) {
        sum += R[i];
        if (sum > rightsum) {
            rightsum = sum;
            maxright = i;
        }
    }

    MAXSUB m;
    m.low = maxleft;
    m.high = maxright;
    m.sum = leftsum + rightsum;  // 正确累加左右独立的最大和
    return m;
}

// 分治法（添加阈值优化，减少递归开销）
MAXSUB FINDMAXIMUMSUBARRAY(const vector<int>& R, int low, int high) {
    if (high == low) {
        return {low, high, R[low]};
    }

    const int THRESHOLD = 50;
    if (high - low + 1 <= THRESHOLD) {
        MAXSUB m = EXHAUSTIONMAXSUBArray(vector<int>(R.begin() + low, R.begin() + high + 1));
        m.low += low;  // 调整子数组索引为原数组索引
        m.high += low;
        return m;
    }

    int mid = (low + high) / 2;
    MAXSUB mleft = FINDMAXIMUMSUBARRAY(R, low, mid);
    MAXSUB mright = FINDMAXIMUMSUBARRAY(R, mid + 1, high);
    MAXSUB mcross = FINDMAXCROSSINGSUBARRAY(R, low, mid, high);

    return (mleft.sum >= mright.sum && mleft.sum >= mcross.sum) ? mleft :
           (mright.sum >= mcross.sum) ? mright : mcross;
}

MAXSUB DYNAMICMAXIMUMSUBARRAY(const vector<int>& R) {
    MAXSUB m = {0, 0, R[0]};
    long currentsum = R[0];
    int currentlow = 0, currenthigh = 0;
    for (int i = 1; i < R.size(); i++) {
        if (R[i] > currentsum + R[i]) { // 若当前元素更大，则重置子数组
            currentlow = currenthigh = i;
            currentsum = R[i];
        } else { // 否则累加到当前子数组
            currenthigh = i;
            currentsum += R[i];
        }
        if (currentsum > m.sum) { // 更新全局最大值
            m.sum = currentsum;
            m.low = currentlow;
            m.high = currenthigh;
        }
    }
    return m;
}

int main() {
    vector<int> R(N);
    MAXSUB m;
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < N; i++)
        R[i] = rand() % 2000 - 1000;

    // 蛮力搜索
    clock_t time_start = clock();
    m = EXHAUSTIONMAXSUBArray(R);
    clock_t time_end = clock();
    cout << "蛮力搜索用时：" << (time_end - time_start) * 1000.0 / CLOCKS_PER_SEC << " 毫秒\n";
    cout << "最大子数组范围：[" << m.low << ", " << m.high << "]，和：" << m.sum << "\n\n";

    // 分治法
    time_start = clock();
    m = FINDMAXIMUMSUBARRAY(R, 0, N - 1);
    time_end = clock();
    cout << "分治法用时：" << (time_end - time_start) * 1000.0 / CLOCKS_PER_SEC << " 毫秒\n";
    cout << "最大子数组范围：[" << m.low << ", " << m.high << "]，和：" << m.sum << "\n\n";

    // 动态规划
    time_start = clock();
    m = DYNAMICMAXIMUMSUBARRAY(R);
    time_end = clock();
    cout << "动态规划用时：" << (time_end - time_start) * 1000.0 / CLOCKS_PER_SEC << " 毫秒\n";
    cout << "最大子数组范围：[" << m.low << ", " << m.high << "]，和：" << m.sum << "\n\n";

    return 0;
}
