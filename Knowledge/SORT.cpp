//排序算法
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 10
#define max(a, b) ((a) > (b)) ? (a) : (b)

void swap (int arr[], int i, int j);
void bubblesort_ascending1 (int arr[]);//冒泡升序1
void bubblesort_ascending2 (int arr[]);//冒泡升序2
void bubblesort_descending1 (int arr[]);//冒泡降序1
void bubblesort_descending2 (int arr[]);//冒泡降序2
void bubblesort_bidirection (int arr[]);//双向冒泡
void preSort(int arr[], int size, int preIndex);//从前冒泡
void backSort(int arr[], int size, int backIndex);//从后冒泡

void selectionsort_ascending (int arr[]);//选择升序
void selectionsort_descending (int arr[]);//选择降序
void secectionsort_ascending_New (int arr[]);//优化选排

void insertionSort(int arr[]);//插入排序
void ShellSort(int arr[]);//希尔排序

void merge(int arr[], int L, int M, int R);//归并排序的merge实现
void mergeSort(int arr[], int L, int R);//归并排序的递归实现

void quickSort(int arr[], int L, int R);//快速排序递归实现
int *partition(int *arr, int L, int R);//快速排序partition实现

int main()
{
    int arr[SIZE];
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
    quickSort (arr,0,SIZE-1);
    for(int i=0; i<SIZE; i++)
        printf("%d ", *(arr+i));
    return 0;
}


//交换两个数的值
/* 异或的性质交换
void swap (int arr[], int i, int j){
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
} */
// 普通交换方法
void swap (int arr[] ,int i ,int j){
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}                                     


//冒泡排序--O(n^2)
/* 升序 */
void bubblesort_ascending1 (int arr[]){//升序1
    int isSwap = 0;//冒泡排序优化，某次已排好便break[外循环优化：趟数减少]
    int position = SIZE-1;//记录最后交换的位置，下次比到该位置即可[内循环优化：比较次数减少]
    if((arr == NULL) || (SIZE < 2)){
        return;
    }
    for(int i=SIZE-1; i>0; i--){
        int newPosition = 0;//每比较一趟，重置
        for(int j=0; j<position; j++){
            if(arr[j] > arr[j+1]){
                swap(arr,j,j+1);
                newPosition = j;
                isSwap = 1;
            }       
        }
        if(!isSwap){//已经排好了就结束
            break;
        }
        position = newPosition;
    }
}
void bubblesort_ascending2 (int arr[]){//升序2
    if((arr == NULL) || (SIZE < 2)){
        return;
    }
    for(int i=0; i<SIZE; i++){
        for(int j=SIZE-1; j>i; j--){
            if(arr[j] < arr[j-1])
                swap(arr,j,j-1);
        }
    }
}  
/* 降序 */
void bubblesort_descending1 (int arr[]){//降序1
    if((arr == NULL) || (SIZE < 2)){
        return;
    }
    for(int i=0; i<SIZE; i++){
        for(int j=SIZE-1; j>i; j--){
            if(arr[j] > arr[j-1])
                swap(arr,j,j-1);
        }
    }
}
void bubblesort_descending2 (int arr[]){//降序2
    if((arr == NULL) || (SIZE < 2)){
        return;
    }
    for(int i=SIZE-1; i>0; i--){
        for(int j=0; j<i; j++){
            if(arr[j] < arr[j+1])
                swap(arr,j,j+1);
        }
    }
}

//鸡尾酒排序[双向冒泡排序]
void bubblesort_bidirection (int arr[]){//鸡尾酒排序
    int preIndex = 0;
    int backIndex = SIZE - 1;

    while(preIndex < backIndex){
        preSort(arr,SIZE,preIndex);
        preIndex++;
        if(preIndex >= backIndex){
            break;
        }
        backSort(arr,SIZE,backIndex);
        backIndex--;
    }
}
void preSort(int arr[], int size, int preIndex){//从前遍历
    for(int i = preIndex + 1; i < size; i++){
        if(arr[preIndex] > arr[i])
            swap(arr,preIndex,i);
    }
}
void backSort(int arr[], int size, int backIndex){//从后遍历
    for(int i = backIndex - 1; i >= 0; i--){
        if(arr[backIndex] < arr[i])
            swap(arr,backIndex,i);
    }
}


//选择排序--O(n^2),选择排序swap异或有可能出问题[当i就是min时异或为0]
//升序、降序，也可以找最大的进行swap
void selectionsort_ascending (int arr[]){//升序
    if((arr == NULL) || (SIZE < 2)){
        return;
    }
    for(int i = 0; i < SIZE-1; i++){
        int MinPosition = i;
        for (int j = i + 1; j < SIZE; j++){
            MinPosition = arr[j] < arr[MinPosition] ? j : MinPosition;
        }
        swap(arr,i,MinPosition);
    }
}
void selectionsort_descending (int arr[]){//降序
    if((arr == NULL) || (SIZE < 2)){
        return;
    }
    for(int i = SIZE-1; i>0; i--){
        int MinPosition = i;
        for(int j = i-1; j>=0; j--){
            MinPosition = arr[j] < arr[MinPosition] ? j : MinPosition;
        }
        swap(arr,i,MinPosition);
    }
}
//选择排序优化[一次找出最大最小值]
void secectionsort_ascending_New (int arr[]){
    if((arr == NULL) || (SIZE < 2)){
        return;
    }
    int k = SIZE - 1;
    for(int i = 0; i < SIZE - 1; i++){
        int minIndex = i;
        int maxIndex = i;
        for(int j = i + 1; j <= k; j++){
            minIndex = arr[j] < arr[minIndex] ? j : minIndex;
            maxIndex = arr[j] > arr[maxIndex] ? j : maxIndex;
        }
        swap(arr,i,minIndex);
        swap(arr,k,maxIndex);
        k--;
    }
}


//插入排序--O(n^2)
void insertionSort(int arr[]){
    for(int i = 1; i < SIZE; i++){//保证0~i有序
        for(int j = i - 1; j >= 0&&arr[j] > arr[j+1]; j--){//i左边的升序条件[降序:'>'改成'<'即可]
            swap(arr,j,j+1);
        }
    }
}

//希尔排序--O(n^1.3)
void ShellSort(int arr[]){
    int h=1;
    while(h<=SIZE/3){//计算gap效率较高
        h=h*3+1;
    }
    for(int gap = h; gap > 0; gap=(gap - 1)/3){//插排间距逐渐减少到1
        for(int i = gap; i < SIZE; i++){//与插排相同
            for(int j = i - gap; j >= 0 && arr[j] > arr[j+gap]; j-=gap){//升序条件“>”[降序:'>'改成'<'即可]
                swap(arr,j,j+gap);
            }
        }
    }
}

//递归求最大值
/*
int getMax(int arr[], int L, int R){
    if(L == R){
        return arr[L];
    }
    int mid=L+((R-L)>>1);//中点[防止整数溢出]
    int leftMax=getMax(arr, L, mid);
    int rightMax=getMax(arr, mid+1, R);
    return max(leftMax,rightMax);
}
*/
//归并排序--O(nlogn)，额外空间复杂度O(n)[help动态数组]
void merge(int arr[], int L, int M, int R){//归并实现
    int *help=(int *)malloc(sizeof(int) *(R - L + 1));//辅助排序的数组
    int p = 0;//辅助数组下表
    int p1 = L;//左边区间的指针
    int p2 = M + 1;//右边区间的指针
    while(p1 <=M && p2 <=R){
        help[p++] = arr[p1] <=arr[p2] ? arr[p1++] : arr[p2++];
    }
    while(p1 <= M){
        help[p++] = arr[p1++];
    }
    while(p2 <= R){
        help[p++] = arr[p2++];
    }
    for(int i = 0; i < R - L + 1; i++){//把排完序的help数组拷贝到原数组
        arr[L + i] = help[i];
    }
    free(help);//释放内存，故只用O(n)的额外空间复杂度
}
void mergeSort(int arr[], int L, int R){//递归实现
    if(L == R){
        return;
    }
    int mid = L + ((R - L) >> 1);//防止整数溢出
    mergeSort(arr, L, mid);//左边递归
    mergeSort(arr, mid + 1, R);//右边递归
    merge(arr, L, mid, R);//归并操作
}
//归并排序-->小和问题


//快速排序1.0-->每次选最右边的数字与右区间最左边的数交换，继续partition
//每次只搞定了一个数O(n^2)
//快速排序2.0-->荷兰国旗问题，每次搞定中间一批数O(n^2)
//划分值打的很偏导致差的情况
//快速排序3.0-->随机选择一个数放到最后的位置[划分值的好坏是概率事件]，根据长期数学期望
//O(n*logn)     额外空间O(logn)
void quickSort(int arr[], int L, int R){
    srand((unsigned) time(NULL));
    if(L < R){
        swap(arr, L + rand() % (R - L + 1), R);
        int *index;
        index = partition(arr, L, R);//储存 = 区的左右边界下标
        quickSort(arr, L, index[0] - 1);// < 区
        quickSort(arr, index[1] + 1, R);// > 区
        free(index);
    }
}
int *partition(int *arr, int L, int R){
    int less = L - 1;// <区的右边界
    int more = R;// >区的左边界
    while(L < more){
        if(arr[L] < arr[R]){//小于划分值，<区域右移，数组下标+1
            swap(arr, ++less, L++);
        }
        else if(arr[L] > arr[R]){//大于划分值，>区域左移，数组下标不变，因为新交换的数还要进行判断
            swap(arr, --more, L);
        }
        else{//等于情况数组下标+1[中间的=区]
            L++;
        }
    }
    swap(arr, more, R);//最后将划分值与>区最左边的值交换
    int *index = (int *)malloc(sizeof(int) * 2);//储存两个边界
    index[0] = less + 1;
    index[1] = more;
    return index;
}