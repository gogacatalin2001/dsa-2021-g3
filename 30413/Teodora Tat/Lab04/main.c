#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int id;
    struct node *left, *right;
} NodeT;
NodeT* createBinaryTree(FILE* f)
{
    NodeT *p;
    char c;
    fscanf(f, "%d", &c);
    if ( c == '*' )
        return NULL;
    else
    {
        p = ( NodeT *) malloc( sizeof( NodeT ));
        if ( p == NULL )
            printf( "we don't have any memory left in createBinaryTree" );
        p->id = c;
        p->left = createBinaryTree(f);
        p->right = createBinaryTree(f);
    }
    return p;
}
void preorder(NodeT *p)
{
    if ( p != NULL )
    {
        printf( "%d ", p->id );
        preorder(p->left);
        preorder(p->right);
    }
}
void inorder(NodeT* p)
{
    if ( p != NULL )
    {
        inorder(p->left);
        printf( "%d ", p->id );
        inorder(p->right);
    }
}
void postorder(NodeT* p)
{
    if ( p != NULL )
    {
        postorder(p->left);
        postorder(p->right);
        printf( "%d ", p->id );
    }
}
int NrOfLeaves(NodeT *p)
{
    if(p==NULL)
        return 0;
    else
        if(p->left==NULL&&p->right==NULL)
        return 1;
        else
            return NrOfLeaves(p->left)+NrOfLeaves(p->right);

}
NodeT* search(NodeT* root, int key)
{
    if(root == NULL)
        return NULL;
    if(root->id==key)
        return root;
    NodeT* left = search(root->left,key);
    if(left!=NULL)
        return left;
    NodeT* right = search(root->right,key);
        return right;
}

void switching(NodeT *p,NodeT *q)
{
    NodeT *aux;
    aux=p;
    p=q;
    q=aux;

}
int maximum(int a, int b)
{
    if(a>=b)
        return a;
    else
        return b;
}
int height(NodeT* p)
{
    if(p==NULL)
        return -1;
    else
        return 1+maximum(height(p->left),height(p->right));
}
int main()
{
   NodeT *root;
    FILE *f = fopen("binaryTree.txt", "r");
    if (f==NULL)
    {
        printf("the file cannot be open\n");
        return -1;
    }
    root = createBinaryTree(f);
    NodeT *a;
    fscanf(f, "%d", &(a->id));
    a=search(root, a->id);
    switch(a->left, a->right);
    preorder(a);
    inorder(a);
    postorder(a);
    int x,y;
    x=NrOfLeaves(root);
    printf("%d the nr of leaves is", &x );
    y=height(root);
    printf("%d the height is", &y );
    return 0;
}
