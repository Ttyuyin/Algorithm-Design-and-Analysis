
void insertsort(int arr[], int n) // 输入的两个数组以及他的长度
{
    int i, j;
    int temp;
    for (i = 1; i < n; i++)
    {

        if (arr[i - 1] > arr[i])
        {
            temp = arr[i];
            j = i - 1;
            do
            {
                arr[j + 1] = arr[j];
                j--;
            } while (j > 0 && arr[j] > temp);
            arr[j + 1] = temp;
        }
    }
}

void insertsort(int arr[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            j = i - 1;
            temp = arr[i];
            do
            {
                arr[j + 1] = arr[j];
                j--;
            } while (j > 0 && arr[j] > temp);
            temp = arr[j + 1];
        }
    }
}

void insertsort(int arr[], int n)
{ // 这个是正确的排序过程
    int i, j;
    int temp;
    for (int i = 1; i < n; i++)
    {

        if (arr[i - 1] > arr[i])
        {
            j = i - 1;
            temp = arr[i];
            do
            {
                arr[j + 1] = arr[j];
                j--;
            } while (j > 0 && arr[j] > temp);
        }
        temp = arr[j + 1];
    }
}

void quicksort(int arr[], int low, int high)
{
    int i, j;
    int temp = arr[0]; // 基准是要变化的，不然后续循环的时候不能一直用没有循环前的第一个基准
    i = low;
    j = high;
    for (int t = 1; t < sizeof(arr); t++)
    { // 数组的长度是不对的
        do
        {
            arr[i + 1] = arr[j];
            j--;
        } while (arr[j] < temp && j >= i); /*do-while 循环至少执行一次，这会导致：

                即使初始时 i 和 j 已满足终止条件，仍然会错误地移动指针并覆盖数据。
                可能引发数组越界（例如当所有元素都小于基准时，j 会一直左移直到越界）。*/

        do
        {
            arr[j] = arr[i];
            i++;
        } while (arr[i] > temp && i <= j);
    }
    arr[i] = temp;
}

void quicksort(int arr[], int low, int high)
{ // 这个是正确的排序
    int temp;
    int i = low, j = high;
    if (i >= j)
        return;
    temp = arr[low];
    while (i < j)
    {
        while (i < j && arr[j] > temp)
            j--;
        if (i < j)
            arr[i++] = arr[j];
        while (i < j && arr[i] < temp)
            i++;
        if (i < j)
            arr[j--] = arr[i];
    }
    arr[i] = temp;
    quicksort(arr, low, i - 1);
    quicksort(arr, i + 1, high);
}


// 合并两个有序子数组
void merge(int q[], int l ,int mid, int r,int temp[]){
    int i=l,j=mid +1; 
    int k=0;//临时数组计数
    while(i<=mid&&j<=r){
        if(q[i]<=q[j]) temp[k++]=q[i++];
        else temp[k++]=q[j++];
    }
    while (i<=mid ) temp[k++]=q[i++];
    while (j<=r) temp[k++]=q[j++];
    for(i=l,k=0;i<r;i++,k++){
        q[i]=temp[k];
    }
}

//归并排序主函数
void merge_sort(int q[], int l, int r){
    if(l>=r) return ;
    int mid = (r-l)/2+l;
    merge_sort(q,l,mid);
    merge_sort(q,mid+1,r);
    merge(q,l,mid,r);
}


/* 首先，我需要回忆C++中sizeof操作符的功能。sizeof用来获取对象或类型的大小（以字节为单位）。
当应用于数组时，比如int arr[] = {1,2,3};，sizeof(arr)会返回整个数组占用的字节数。
例如，如果数组有3个int元素，每个int占4字节，那么sizeof(arr)就是12字节 */

void merge(int a[], int low, int mid, int high,int temp[]){

    int i=low,j=mid+1;
    int  k = 0;
    while (i<=mid&&j<=high){
        if(a[i]<a[j]) temp[k++]=a[i++];
        else temp[k++]=a[j++];
    }
    while (i<=mid) temp[k++]=a[i++];
    while (j<=high) temp[k++]=a[i++];
    a[i]=temp[k];
}

void merge(int arr[],int low,int mid,int high,int temp[]){
    int i=low,j=mid+1;
    int k= 0;
    while(i<=mid&&j<=high){
        if(arr[i]<arr[j]) temp[k++]= arr[i++];
        else temp[k++]= arr[j++];
    }
    while (i<=mid) temp[k++]=arr[i++];
    while (j<=high) temp[k++]=arr[j++];
    arr[i]=temp[k];
}

void merge_sort(int a[], int low, int high){
    if(low>=high) return ;
    int mid = low + (high-low)/2;
    merge_sort(a,low,mid);
    merge_sort(a,mid+1,high);
    merge(a,low,mid,high);
}

/* int main(){
    int size=N;
    int *R = (int *)malloc(sizeof(int)*size);
    int time_start,time_end;

    srand(time(NULL));

    for(int i=0;i<N;i++)
    R[i]=rand();
    time_start=clock();
    insertsort(R,N);
    time_end=clock();
    cout<<time_end-time_start<<endl;

    for(int i=0;i<N;i++)
    R[i]=rand();
    time_start=clock();
    quicksort(R,0,N-1);
    time_end=clock();
    cout<<time_end-time_start<<endl;

    for(int i=0;i<N;i++)
    R[i]=rand();
    time_start=clock();
    merge_sort(R,0,N-1);
    time_end=clock();
    cout<<time_end-time_start<<endl;

    free(R);

    return 0;
} */

void bottomupsort(int arr[],int n)
    {
        int *temp = new int [n];
        for (int width=1;width<n;width*=2){
            for (int i=0;i<n;i=i+2*width){
                int left=i;
                int mid = min(left+width-1,n-1);
                // 中间的位置在哪里，就在最左（left）向右看一个步长（width），只不过受位置为0，所以要去减去1.
                //找min主要是为了防止越界。
                int rigth=min (left+2*width-1,n-1);
                merge (arr,left,mid,rigth,temp);
            }
        }
        delete []temp;

}

void bottomupsort(int arr[],int n){
    int *temp = new int [n];
    for (int width=1;width<n;width*=2){
        for(int i=0;i<n;i=i+2*width){
            int left = i;
            int mid = min(left+width-1,n-1);
            int rigth=min (left+2*width-1,n-1);
            merge(arr,left,mid,right,temp);
        }
    }
}

void bottomupsort(int arr[],int n){
    int *temp = new int [n];
    for(int width=1;width<n;width*=2){
        for (int i=0;i<n;i=i+2*width){
            int left=i;
            int mid = min (left+width-1,n-1);
            int rigth = min (left + 2* width -1,n-1);
            merge (arr,left ,mid right ,temp);
        }
    }
}