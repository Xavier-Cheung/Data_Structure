#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSize 100

typedef struct TreeNode {
    char data;
    int tag;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *BitTree;

TreeNode *BuildTree(char PreOrder[], char InOrder[], int Size);
TreeNode *process(char PreOrder[], int P_left, int P_right, char InOrder[], int I_left, int I_right);
void InitTree (BitTree &Tree);
void BackOrder_Print (BitTree Tree, char y);
void Level_Print(BitTree Tree, int Size);
int Weight (BitTree &Tree, char x);
void GetPath (BitTree Tree, char x);


int main() {
    char PreOrder[MaxSize+1] = {0};
    char InOrder[MaxSize+1] = {0};
    char Path[MaxSize+1] = {0};
    char x, y;
    printf ("请输入前序遍历序列:\n");
    scanf("%s", PreOrder);
    printf ("请输入中序遍历序列:\n");
    scanf("%s", InOrder);
    int Size = strlen(PreOrder);
    BitTree Tree = (BitTree) malloc (sizeof(TreeNode));
    Tree = BuildTree (PreOrder, InOrder, Size);
    y = Tree -> data;
    printf("打印该二叉树后序遍历如下:\n");
    BackOrder_Print (Tree, y);
    printf("\n打印该二叉树层序遍历如下:\n");
    Level_Print(Tree,Size);
    printf ("\n请输入要查找的结点的值:\n");
    getchar();
    scanf("%c", &x);
    int i = Weight(Tree, x);
    if(i){
        printf("嚯嚯嚯!找到啦! 你看:\n");
        GetPath (Tree, x);
    } 
    else
        printf("这棵树里没有该结点hhh!!!\n");
    return 0;
}

void InitTree (BitTree &Tree) {
    Tree -> data = 0;
    Tree -> left = NULL;
    Tree -> right = NULL;
}

TreeNode* BuildTree(char PreOrder[], char InOrder[], int Size) {
    return process(PreOrder, 0, Size-1, InOrder, 0, Size-1);//递归构造
}

TreeNode *process(char PreOrder[], int P_left, int P_right, char InOrder[], int I_left, int I_right) {
    if(P_left > P_right) {//数组为0
        return NULL;
    }
    TreeNode *root = (TreeNode *) malloc (sizeof(TreeNode));//构造节点，并初始化
    root -> data = PreOrder[P_left];
    root -> left = NULL;
    root -> right = NULL;
    root -> tag = 0;
    for(int i = I_left; i <= I_right; i++){//切割中序数组
        if(InOrder[i] == PreOrder[P_left]){//找到了切割点
            root -> left = process (PreOrder, P_left+1, P_left+1 + i-1-I_left, InOrder, I_left, i-1);
            root -> right = process (PreOrder, P_left+1 + i-I_left, P_right, InOrder, i+1, I_right);//直接根据中序数组切割点的元素个数，推导前序数组的切割点
            break;
        }
    }
    return root;
}

void BackOrder_Print (BitTree Tree,char y){
    if(!Tree) return;
    BackOrder_Print (Tree -> left, y);
    BackOrder_Print (Tree -> right, y);
    if(Tree -> data != y)
        printf("%c -> ", Tree -> data, Tree -> tag);
    else
        printf("%c\n", Tree -> data, Tree -> tag);
}

int Weight (BitTree &Tree, char x){
    if(Tree -> data == x){
        Tree -> tag = 1;
    }
    else{
        if(Tree -> left){
            Tree -> tag += Weight (Tree -> left, x);
        }
        if(Tree -> right){
            Tree -> tag += Weight(Tree -> right,x);
        }
    }
    return Tree -> tag;
}

void GetPath (BitTree Tree, char x){
    if(Tree == NULL) return;
    if(Tree -> tag == 1){
        if(Tree -> data != x)
            printf("%c -> ", Tree -> data);
        else
            printf("%c\n", Tree -> data);
    }  
    GetPath (Tree -> left, x);
    GetPath (Tree -> right, x);
}

void Level_Print(BitTree Tree,int Size)  //层序遍历
{
    TreeNode *temp[100];
    int rear = 0;
    int front = 0;
    int i = 0;
    temp[rear++] = Tree;  //先保存二叉树根节点 
    while (rear > front)
    {
        if (temp[front])
        {
            if(i != Size-1)
                printf("%c -> ", temp[front] -> data);
            else
                printf("%c\n", temp[front] -> data);
            temp[rear++] = temp[front] -> left;
            temp[rear++] = temp[front] -> right;
            i++;
        }
        front++;
    }
}
