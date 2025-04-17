//求最大和子数组算法实验：蛮力搜索、分治法、动态规划
#include <stdlib.h> 
#include <time.h>
#include <limits.h>
#include <stdio.h>

#define N 1000000

struct MAXSUB
{
	int    low;
	int    high;
	long  sum;
};

struct MAXSUB EXHAUSTIONMAXSUBArray(int R[], int n) {
    struct MAXSUB m = {0, 0, R[0]};
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

//分治法
// 计算跨越中点的最大子数组（修复右半部分计算错误）
struct MAXSUB FINDMAXCROSSINGSUBARRAY(int R[], int low, int mid, int high) {
    // 计算左半部分（从mid向左）
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

    // 计算右半部分（从mid+1向右，独立计算）
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

    // 合并左右部分
    struct MAXSUB m;
    m.low = maxleft;
    m.high = maxright;
    m.sum = leftsum + rightsum;  // 正确累加左右独立的最大和
    return m;
}

// 分治法（添加阈值优化，减少递归开销）
struct MAXSUB FINDMAXIMUMSUBARRAY(int R[], int low, int high) {
    // 递归终止条件
    if (high == low) {
        struct MAXSUB m;
        m.low = low;
        m.high = high;
        m.sum = R[low];
        return m;
    }

    // 阈值优化：当子数组长度较小时使用暴力法
    const int THRESHOLD = 50;
    if (high - low + 1 <= THRESHOLD) {
        struct MAXSUB m = EXHAUSTIONMAXSUBArray(R + low, high - low + 1);
        m.low += low;  // 调整子数组索引为原数组索引
        m.high += low;
        return m;
    }

    // 分治递归
    int mid = (low + high) / 2;
    struct MAXSUB mleft = FINDMAXIMUMSUBARRAY(R, low, mid);
    struct MAXSUB mright = FINDMAXIMUMSUBARRAY(R, mid + 1, high);
    struct MAXSUB mcross = FINDMAXCROSSINGSUBARRAY(R, low, mid, high);

    // 返回三者中的最大值
    return (mleft.sum >= mright.sum && mleft.sum >= mcross.sum) ? mleft :
           (mright.sum >= mcross.sum) ? mright : mcross;
}


struct MAXSUB DYNAMICMAXIMUMSUBARRAY(int R[], int n) {
    struct MAXSUB m = {0, 0, R[0]};
    long currentsum = R[0];
    int currentlow = 0, currenthigh = 0;
    for (int i = 1; i < n; i++) {
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

int main()
{
    int *R = (int*)malloc(N * sizeof(int));
    struct MAXSUB m;
    srand(time(0));
    for (int i = 0; i < N; i++)
        R[i] = rand() % 2000 - 1000;

    // 蛮力搜索
    clock_t time_start = clock();
    m = EXHAUSTIONMAXSUBArray(R, N);
    clock_t time_end = clock();
    printf("蛮力搜索用时：%ld 毫秒\n", time_end - time_start);
    printf("最大子数组范围：[%d, %d]，和：%ld\n\n", m.low, m.high, m.sum);

    // 分治法
    time_start = clock();
    m = FINDMAXIMUMSUBARRAY(R, 0, N - 1);
    time_end = clock();
    printf("分治法用时：%ld 毫秒\n", time_end - time_start);
    printf("最大子数组范围：[%d, %d]，和：%ld\n\n", m.low, m.high, m.sum);

    // 动态规划
    time_start = clock();
    m = DYNAMICMAXIMUMSUBARRAY(R, N);
    time_end = clock();
    printf("动态规划用时：%ld 毫秒\n", time_end - time_start);
    printf("最大子数组范围：[%d, %d]，和：%ld\n\n", m.low, m.high, m.sum);

    free(R);
    return 0;
}
