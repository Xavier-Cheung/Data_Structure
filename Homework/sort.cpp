#include<stdio.h>
#include<stdlib.h>
#include <time.h>

clock_t Start;
clock_t End;

void InsertSort(int arr[], int s, int t){
    int j;
    for(int i = s+1;i<=t;i++){
        if(arr[i]<arr[i-1]){
            arr[0]=arr[i];//将r[i]放到0位置作为空置位 
            for(j=i-1;arr[0]<arr[j];j--){
                arr[j+1]=arr[j];//从i之前找合适的位置插，没找到就后移 
            }
            arr[j+1]=arr[0];//插入到合适的位置 
        }
    }
}
void swap(int *r, int a, int b){
	int temp = r[a];
	r[a] = r[b];
	r[b] = temp;
}
void Find(int *r,int low, int high){//计算数组中间的元素的下标 ，使用三数取中法选择枢轴    
    int mid = low + ((high - low) >> 1);
    if (r[mid] > r[high]){
    swap(r, mid, high);
    }
    if (r[low] > r[high]){
    swap(r, low, high);
    }
    if (r[mid] > r[low]){
    swap(r, mid, low);
    }
}
int partition(int *r,int low,int high,int flag){
    if(flag==1){//若三者取中则先找到“中间元素” 
    	Find (r, low, high); 
    }
    r[0]=r[low];
    while(low<high){
        while(low<high&&r[high]>r[0]){
            high--;
        }
        if(low<high){
            r[low]=r[high];
            low++;
        }
        while(low<high&&r[low]<r[0]){
            low++;
        }
        if(low<high){
            r[high]=r[low];
            high--;
        }
    }
    r[low]=r[0];
    return low;
}
void quicksort(int *r,int s,int t,int flag){//快速排序 
    int i;
    if(s<t){
        if(t-s>=20){//长度大于20用快排 
            i=partition(r,s,t,flag);
            quicksort(r,s,i-1,flag);
            quicksort(r,i+1,t,flag);
        }
        else{//小于20用插入排序 
            InsertSort(r,s,t);
        }
    }
}

int main(){
    int n,i,k;
    FILE *fp; 
    double time2,time1;
    int r[50000],z[50000];
    printf("请输入待排序列长度:");
    scanf("%d",&n);
    if((fp = fopen("D:\\sss\\123.txt","r")) == NULL){
    	printf("读取文件失败\n");
		exit(0); 
	}
	else{
		printf("文件打开成功\n");
		for(i=1;i<=n;i++){
			fscanf(fp, "%d ",&r[i]);
        	z[i]=r[i];
    	}
	}
    
    Start = clock();
    quicksort(r,1,n,1);  //flag=1,time1表示使用 
    End = clock();
    time1= ((double)(End - Start)) / CLK_TCK;
    //for(k=1;k<=n;k++){
    //    printf("%d ",r[k]);
    //}
    Start = clock();
    quicksort(z,1,n,0);   //flag=0,time2表示未使用 
    End = clock();
    time2= ((double)(End - Start)) / CLK_TCK;
    //for(k=1;k<=n;k++){
    //   printf("%d ",z[k]);
    //}
    printf("函数使用三者取中法共用时：%.6lf\n",time1);
    printf("函数不使用三者取中法共用时：%.6lf\n",time2);
    return 0;
}
