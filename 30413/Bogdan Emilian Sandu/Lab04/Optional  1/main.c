#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct node
{
    char exp;
    struct node *left, *right;
}NodeT;
typedef struct stackN
{
    struct stackN *next;
    NodeT *tn;//tree node
}StackN;
typedef struct stack
{
    StackN *bottom;//bottom ptr
    StackN *top;//top ptr
    int nr;//count of elements
}StackT;

StackN *createSN(NodeT *m)
{
    StackN *p;
    p=(StackN*)malloc(sizeof(StackN));
    if(p==NULL) exit(1);
    p->tn=m;
    p->next=NULL;
}

NodeT *createNode(char c)
{
    NodeT *p;
    p=(NodeT*)malloc(sizeof(NodeT));
    if(p==NULL) exit(1);
    p->exp=c;
    p->left=NULL;
    p->right=NULL;
    return p;
}
StackT *createEmptyS()
{
    StackT *p;
    p=(StackT*)malloc(sizeof(StackT));
    if(p==NULL) exit(1);
    p->bottom=NULL;
    p->top=NULL;
    p->nr=0;
}
void pushS(StackT *stackPtr,NodeT *p)
{
    StackN *m=createSN(p);
    if(stackPtr->nr==0)
        {
            stackPtr->top=stackPtr->bottom=m;
            m->next=NULL;
        }
    else
        {
            m->next=stackPtr->top;
            stackPtr->top=m;
        }
    stackPtr->nr++;
}
StackN *popS(StackT *stackPtr)
{
    StackN *p;
    p=stackPtr->top;
    if(stackPtr->nr==0) return NULL;
    else if(stackPtr->nr==1)
        stackPtr->top=stackPtr->bottom=NULL;
    else
        stackPtr->top=stackPtr->top->next;
    return p;
}
bool isOp(char c)
{
    if(c=='+' || c=='-' || c=='*' || c=='/') return true;
    else return false;
}
NodeT *createTree(char *s)
{
    NodeT *root,*nd;
    StackT *stackPtr=createEmptyS();
    StackN *m,*n;
    for(int i=0;i<strlen(s);i++)
    {
        printf("%i %d\n",i,strlen(s));
        if(isOp(s[i])==false)
    {
        nd=createNode(s[i]);
        pushS(stackPtr,nd);
    }
    else
    {
        m=popS(stackPtr);
        n=popS(stackPtr);
        nd=createNode(s[i]);
        nd->left=n->tn;
        nd->right=m->tn;
        pushS(stackPtr,nd);
        if(i==strlen(s)-1) root=nd;
        free(m);
        free(n);
    }
    }
    return root;
}
void postfix(NodeT *root)
{
    if(root==NULL) return;
    postfix(root->left);
    postfix(root->right);
    printf("%c ",root->exp);
}
void prefix(NodeT *root)
{
    if(root==NULL) return;
    printf("%c ",root->exp);
    prefix(root->left);
    prefix(root->right);
}
void inorder(NodeT *root)
{
    if(root==NULL) return;
    inorder(root->left);
    printf("%c ",root->exp);
    inorder(root->right);
}
int main()
{
    char s[20];
    NodeT *root;
    scanf("%s",s);
    root=createTree(s);
    postfix(root);
    printf("\n");
    inorder(root);
    return 0;
}
