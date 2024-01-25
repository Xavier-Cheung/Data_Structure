#include<stdio.h>
#define MAX 100
#define INF 10086
int mat[MAX][MAX];
int dest[MAX][MAX];
int prim(int m);
void shift(int miny,int v2[],int m);
int main(){
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&mat[i][j]);
			if(mat[i][j]==0){
				mat[i][j]=INF;
			}
		}
	}
	int Lweight=prim(m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",dest[i][j]);
		}
		printf("\n");
	}
}
int prim(int m){
	int v1[MAX]={0,1};
	int v2[MAX]={0};
	int minx=1;
	int miny=1;
	for(int i=1;i<=m-1;i++){
		v2[i]=i+1;
	}
	for(int i=1;i<=m-1;i++){
		for(int j=1;j<=i;j++){
			for(int k=i;k<=m-1;k++){
				if(mat[v1[j]][v2[k]]<mat[minx][miny]){
					minx=v1[j];
					miny=v2[k];
					if (minx>miny){
					minx=v2[k];
					miny=v1[j];
					}
					
					//printf("%d %d\n",v1[j],v2[k]);
				}
			}
		}
		//printf("%d %d\n",minx,miny);
		dest[minx][miny]=mat[minx][miny];
		dest[miny][minx]=mat[minx][miny];
		v1[i+1]=miny;
		shift(miny,v2,m);
		minx=1;miny=1;
	}
}
void shift(int miny,int v2[],int m){
	int temp;
	for(int i=1;i<=m;i++){
		if(v2[i]!=INF){
			v2[miny-1]=v2[i];
			v2[i]=INF;
			break;
		}
	}
}
/*0 2 3 0 0 0 0 0
2 0 0 2 0 0 0 0
3 0 0 1 0 0 0 0
0 2 1 0 2 4 0 0
0 0 0 2 0 1 2 0
0 0 0 4 1 0 2 1
0 0 0 0 2 2 0 3
0 0 0 0 0 1 3 0*/
