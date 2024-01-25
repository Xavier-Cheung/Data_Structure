#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define INF 10086
struct edge{
	int lside;
	int bside;
	int weight;
};
void visit(int visited[],int level,int m);
typedef struct edge edge;
int p[MAX][MAX];
int dest[MAX][MAX];
edge edg[MAX*MAX];
int remov(int m);
void edgepai(int count);
int main(){
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&p[i][j]);
		}
	}
	int weigh=remov(m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",p[i][j]);
		}
		printf("\n");
	}
}
int remov(int m){
	int count=0;
	int temp;
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
	int visited[MAX]={0};
	int flag=1;
	for(int i=1;i<=count;i++){
		flag=1;
		for(int j=1;j<=m;j++){
			visited[j]=0;
		}
		temp=p[edg[i].lside][edg[i].bside];
		p[edg[i].lside][edg[i].bside]=0;
		p[edg[i].bside][edg[i].lside]=0;
		
		visit(visited,1,m);
		for(int j=1;j<=m;j++){ 
			if(visited[j]==0){
				flag=0;break;
			} 
		}
		if(flag==0){
			p[edg[i].lside][edg[i].bside]=temp;
			p[edg[i].bside][edg[i].lside]=temp;
		}
	}
}
void edgepai(int count){
	edge temp;
	for(int i=1;i<=count;i++){
		for(int j=1;j<count;j++){
			if(edg[j].weight<edg[j+1].weight){
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
void visit(int visited[],int level,int m){
	for(int i=1;i<=m;i++){
		if(p[level][i]!=0&&visited[i]!=1){
			visited[level]=1;
			visited[i]=1;
			visit(visited,i,m);
		}
	}
}
