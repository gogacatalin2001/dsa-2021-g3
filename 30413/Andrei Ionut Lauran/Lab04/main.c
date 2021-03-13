#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    char id;
    struct node_type *left,*right;
}NodeT;

void fatalError(const char *msg)
{
    printf(msg);
    printf("\n");
    exit(1);
}

void preorder(NodeT *p)
{
    if(p!=NULL)
    {
        printf("%d ",p->id);
        preorder(p->left);
        preorder(p->right);
    }
}

void inorder(NodeT *p)
{
    if(p!=NULL)
    {
        inorder(p->left);
        printf("%d ",p->id);
        inorder(p->right);
    }
}

void postorder(NodeT *p)
{
    if(p!=NULL)
    {
        postorder(p->left);
        postorder(p->right);
        printf("%d ",p->id);
    }
}

NodeT *createBinTree(int branch,NodeT *parent)
{
    NodeT *p;
    int id;
    if(branch==0)
        printf("Root is [0 to end]:");
    else if(branch==1)
        printf("Left child of %d is [0 to end]:",parent->id);
    else
        printf("Right child of %d is [0 to end]:",parent->id);
    scanf("%d",&id);
    if(id==0)
        return NULL;
    else
    {
        p = (NodeT*)malloc(sizeof(NodeT));
        if(p==NULL)
            fatalError("Out of space");
        p->id=id;
        p->left = createBinTree(1,p);
        p->right = createBinTree(2,p);
    }
    return p;
}


int nrLeaves(NodeT *root)
{
    if(root->left==NULL && root->right==NULL)
        return 1;
    return nrLeaves(root->left) + nrLeaves(root->right);
}

int height(NodeT *root)
{
    if(root==0)
        return -1;
    int LeftHeight=height(root->left);
    int RightHeight=height(root->right);
    if(LeftHeight>RightHeight)
        return LeftHeight+1;
    else
        return RightHeight+1;
}

void findAndSwap(NodeT *root,int givenID)
{
    if(root == NULL)
        return;
    if(root->id==givenID)
    {
        NodeT *aux = root->left;
        root->left = root->right;
        root->right = aux;
        return;
    }
    findAndSwap(root->left,givenID);
    findAndSwap(root->right,givenID);
}

void list(NodeT *root)
{
    printf("\nPreorder listing:\n");
    preorder(root);
    printf("\nInorder listing:\n");
    inorder(root);
    printf("\nPostorder listing:\n");
    postorder(root);
    printf("\n");
}

int main()
{
    int id;
    NodeT *root = createBinTree(0,NULL);
    list(root);
    printf("\nIntroduce the ID of the parent node of the subtrees to swap:");
    scanf("%d",&id);
    findAndSwap(root,id);
    printf("\nListing after swapping:\n");
    list(root);
    printf("\nHeight of the tree is:%d\n",height(root));
    printf("\nNr of leaves:%d\n",nrLeaves(root));
    return 0;
}