#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
#define N 1000

//插入函数
void insertsort(int arr[],int n){
    for(int i=1;i<n;i++){
        int temp=arr[i];
        int j=i-1;
        while (j>=0&&arr[j]>temp){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }
}

//快速排序
int partition (int arr[],int low,int high){
    int pivot = arr[(low+high)/2];
    int i=low-1;
    int j=high+1;
    while(true){
        do{
            i++;
        }while(arr[i]<pivot);
        do{
            j--;
        }while(arr[j]>pivot);
        if(i>=j) return j;
        swap(arr[i],arr[j]);
    }
}

void quicksort(int arr[],int low,int high){
    if(low>=high) return ;
    int p= partition(arr,low,high);
    quicksort(arr,low,p);
    quicksort(arr,p+1,high);
}

//归并排序
void merge(int arr[],int low,int mid,int high,int temp[]){
    int i=low,j=mid+1,k=0;
    while(i<=mid&&j<=high){
        if(arr[i]<=arr[j]) temp[k++]=arr[i++];
        else temp[k++]=arr[j++];
    }while (i <= mid) temp[k++] = arr[i++];
    while (j <= high) temp[k++] = arr[j++];
    for (i = low, k = 0; i <= high; i++, k++) arr[i] = temp[k];
}//这个仅仅是把左右两个数组对应的元素进行比较然后进行排序，依次排序后的结果不一定在整体上是有序的。

void merge_sort(int arr[], int low, int high, int temp[]) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    merge_sort(arr, low, mid, temp);
    merge_sort(arr, mid + 1, high, temp);
    merge(arr, low, mid, high, temp);
}

//自底向上归并排序
void BottomUpSort(int arr[], int n) {
    int* temp = new int[n];
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = min(left + width - 1, n - 1);  
            //第一个子数组的范围是 [left, mid]，长度为 width。
            //eft + width - 1 是理想情况下第一个子数组的结束位置。
            //min 函数确保当剩余元素不足 width 时，mid 不会超出数组末尾（n - 1）。
            int right = min(left + 2 * width - 1, n - 1);
            merge(arr, left, mid, right, temp);
        }
    }
    delete[] temp;
}

//主函数
int main() {
    int size = N;
    int* R = new int[size];
    clock_t time_start, time_end;

    // 插入排序
    srand(time(NULL));
    for (int i = 0; i < N; i++) R[i] = rand();
    time_start = clock();
    insertsort(R, N);
    time_end = clock();
    cout << "Insertion Sort: " << time_end - time_start << "ms" << endl;

    // 快速排序
    for (int i = 0; i < N; i++) R[i] = rand();
    time_start = clock();
    quicksort(R, 0, N - 1);
    time_end = clock();
    cout << "Quick Sort: " << time_end - time_start << "ms" << endl;

    // 归并排序
    int* temp = new int[N]; // 预分配临时数组
    for (int i = 0; i < N; i++) R[i] = rand();
    time_start = clock();
    merge_sort(R, 0, N - 1, temp);
    time_end = clock();
    cout << "TopDown Merge: " << time_end - time_start << "ms" << endl;
    delete[] temp;

    //自底向上归并排序
    for (int i = 0; i < N; i++) R[i] = rand();
    time_start = clock();
    BottomUpSort(R, N);
    time_end = clock();
    cout << "BottomUp Merge: " << time_end - time_start << "ms" << endl;

    delete[] R;
    return 0;
}