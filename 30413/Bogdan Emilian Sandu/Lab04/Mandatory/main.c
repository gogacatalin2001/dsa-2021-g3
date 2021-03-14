#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *right, *left;
}NodeT;

NodeT *createBinTree()
{
    int d;
    scanf("%d",&d);
    if(d==-1) return NULL;
    NodeT *p;
    p=(NodeT*)malloc(sizeof(NodeT));
    if(p==NULL)
        exit(1);
    p->val=d;
    p->left=createBinTree();
    p->right=createBinTree();
}
int maxim(int a, int b)
{
    if(a>b) return a;
    else return b;
}

void preorder(NodeT *p)
{
    if(p!=NULL)
    {
        printf("%d ",p->val);
        preorder(p->left);
        preorder(p->right);
    }
}
void inorder(NodeT *p)
{
    if(p!=NULL)
    {
        inorder(p->left);
        printf("%d ",p->val);
        inorder(p->right);
    }
}
void postorder(NodeT *p)
{
    if(p!=NULL)
    {
        postorder(p->left);
        postorder(p->right);
        printf("%d ",p->val);
    }
}
void interChange(NodeT *p)
{
    NodeT *aux;
    if(p==NULL) return;
    aux=p->left;
    p->left=p->right;
    p->right=aux;
    interChange(p->left);
    interChange(p->right);
}
int heightTree(NodeT *root)
{
    if(root==NULL) return 0;
    return maxim(heightTree(root->left),heightTree(root->right))+1;
}
int leavesNr(NodeT *root)
{
    if(root==NULL) return 0;
    if(root->left==NULL && root->right==NULL) return 1;
    return leavesNr(root->left)+leavesNr(root->right);
}
int main()
{
    NodeT *root;
    root=createBinTree();
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    interChange(root);
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    printf("%d\n",heightTree(root));
    printf("%d",leavesNr(root));
    return 0;

}
