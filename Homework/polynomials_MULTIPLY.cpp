#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
    float coef;
    int expon;
    struct LNode *next;
} LNode, *LinkList;


void InitList(LinkList &L);//初始化链表
void displayNode(LinkList head);//遍历链表
LinkList CreatList(LinkList &L);//创建链表
LinkList ReverseList(LinkList &L);//反转链表


int main(){
    LNode *PA, *PB, *PC;
    InitList(PA);InitList(PB);InitList(PC);
    PA = CreatList(PA);//默认降幂输入
    PB = CreatList(PB);
//displayNode(PA);
//displayNode(PB);
    LinkList pa = PA -> next, pb = PB -> next, tail = PC;
    int expon_Max = (pa -> expon) + (pb -> expon);//最大指数
    PB = ReverseList(PB);
    PA = ReverseList(PA);
//displayNode(PA);
//displayNode(PB);
    pa = PA -> next; pb = PB -> next;
    int expon_Min = (pa -> expon) + (pb -> expon);//最小指数
//printf("%d \n",expon_Min);
    PA = ReverseList(PA);
//displayNode(PA);
//displayNode(PB);
    for(int i = expon_Max; i >= expon_Min; i--){
        float coef_mul = 0.0;//每一项的系数
        pa = PA -> next;
        pb = PB -> next;
        while(pa && pb){
            if(pa -> expon + pb -> expon < i){
                pb = pb -> next;
            }
            else if(pa -> expon + pb -> expon > i){
                pa = pa -> next;
            }
            else{
                coef_mul+= (pa -> coef) * (pb -> coef);
                pa = pa -> next;
                pb = pb -> next;
            }
        }
        if(coef_mul != 0.0){
            LNode *temp = (LNode *) malloc (sizeof(LNode));
            temp -> coef = coef_mul;
            temp -> expon = i;
            tail -> next = temp;
            tail = temp;
        }
    }
    tail -> next =NULL;
    displayNode(PC);
    return 0;
}

void InitList(LinkList &L){
    L = (LNode *) malloc (sizeof(LNode));
    if(L == NULL)
        return;
    L -> next = NULL;
}

LinkList CreatList(LinkList &L){
    float x; int y;
    scanf("%f %d",&x, &y);
    L = (LinkList) malloc (sizeof(LNode));
    LNode *temp, *tail = L;
    while(x != 0.0){
        temp = (LNode *) malloc (sizeof(LNode));
        temp -> coef = x;
        temp -> expon = y;
        tail -> next = temp;
        tail = temp;
        scanf("%f %d",&x, &y);
    }
    tail -> next = NULL;
    return L;
}

LinkList ReverseList(LinkList &L){
    if(L -> next == NULL || L -> next -> next == NULL)
        return L;
    	LNode * pre = NULL, * s = NULL;
	LNode* p = L->next;
	while (p)
	{
		s = p;
		p = p->next;
		s->next = pre;//ai+1指向ai
		pre = s;
	}
    L -> next =pre;
    return L;
}

void displayNode(LinkList head)
{
    LNode *p = head->next;          //p指向首元结点
    while(p)
    {
        printf("%.2f %d\t",p->coef,p->expon);  //输出数据 
        p = p->next;             //移向下一个结点
    }
    printf("\n");
}
