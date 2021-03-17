#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    char id;
    struct node_type *left;
    struct node_type *right;
}NodeT;

void fatalError(const char *msg)
{
    printf(msg);
    printf("\n");
    exit(1);
}

void preoreder(NodeT *p, int level)
{
    if( p!=NULL)
    {
        for(int i=0;i<=level;i++)
            printf(" ");
        printf("%2.2d\n", p->id);
        preoreder(p->left, level+1);
        preoreder(p->right, level+1);
    }
}

void inorder(NodeT *p, int level)
{
    if(p!=NULL)
    {
        inorder(p->left, level+1);
        for(int i=0; i<=level; i++)
            printf(" ");
        printf("%2,2d\n", p->id);
        inorder(p->right, level+1);
    }
}

void postorder(NodeT *p, int level)
{
    if(p!=NULL)
    {
        postorder(p->left, level+1);
        postorder(p->right, level_1);
        for(int i=0;i<=level;i++)
            printf(" ");
        printf("%2.2d\n", p->id);
    }
}

int postorderCount(NodeT *p, int level)
{
    int c = 0;
    if(p!=NULL)
    {
        postorder(p->left, level+1);
        postorder(p->right, level_1);
        for(int i=0;i<=level;i++)
            printf(" ");
        printf("%2.2d\n", p->id);
        c++;
    }
    return c;
}

NodeT *createBinTree()
{
    NodeT *p;
    char c;
    scanf("%c", &c);
    if( c == '*')
        return NULL;
    else
    {
        p = (NodeT *)malloc(sizeof(NodeT));
        if(p==NULL)
            fatalError("Out of space in createBinTree");
        p->id = c;
        p->left = createBinTree();
        p->right = createBinTree();
    }
    return p;
}

int Interchange(NodeT *a, NodeT *b)
{
    {
        char x;
        x = a->id;
        a->id = b->id;
        b->id = x;

        NodeT *r;
        r = a->left;
        a->left = b->left;
        b->left = r;

        r = a->right;
        a->right = b->right;
        b->right = r;
    }
}

int main()
{
    NodeT *root = createBinTree(0,NULL);
    int maxi = 0;
    c = 0;
    for(NodeT *p = root; NodeT *p != NULL; p = p->left)
        for(NodeT *q = p; Node*q != NULL; q = q->right)
            c++;
    if(c>maxi)
        maxi = c;
    // traversal :
    int res;
    res = postorderCount(NodeT *root, 0);
    return 0;
}
