#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define INF 10086
struct edge{
	int lside;
	int bside;
	int weight;
};
typedef struct edge edge;
int p[MAX][MAX];
int dest[MAX][MAX];
edge edg[MAX*MAX];
int kruskal(int m);
int find(int n,int father[]);
void edgepai(int count);
int main(){
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&p[i][j]);
		}
	}
	int weigh=kruskal(m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",dest[i][j]);
		}
		printf("\n");
	}
}
int kruskal(int m){
	int count=0;
	int father[MAX*MAX];
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			if(p[i][j]!=0){
				count++;
				edg[count].lside=i;
				edg[count].bside=j;
				edg[count].weight=p[i][j];
				//printf("%d %d %d\n",edg[count].lside,edg[count].bside,count);
			}
		}
	}
	//printf("%d\n",count);
	edgepai(count);
	for(int i=1;i<=m;i++){
		father[i]=i;
	}
	for(int i=1;i<=count;i++){
		if(find(edg[i].lside,father)==find(edg[i].bside,father)){
			continue;
		}
		else{
			father[find(edg[i].bside,father)]=find(edg[i].lside,father);
			dest[edg[i].lside][edg[i].bside]=edg[i].weight;
			dest[edg[i].bside][edg[i].lside]=edg[i].weight;
		}
	}
}
void edgepai(int count){
	edge temp;
	for(int i=1;i<=count;i++){
		for(int j=1;j<count;j++){
			if(edg[j].weight>edg[j+1].weight){
				temp=edg[j];
				edg[j]=edg[j+1];
				edg[j+1]=temp;
			}
		}
	}
	for(int i=1;i<=count;i++){
		//printf("%d %d\n",edg[i].lside,edg[i].bside);
	}
}
int find(int n,int father[]){
	if(father[n]==n){
		return n;
	}
	else{
		return find(father[n],father);
	}
}
