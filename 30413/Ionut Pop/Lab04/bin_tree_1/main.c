#include <stdio.h>
#include <stdlib.h>

typedef struct node_type{
    char id;
    struct node_type *left, *right;
} NodeT;

void fatalError(const char *msg){
    printf("msg");
    printf("\n");
    exit(1);
}

void preorder(NodeT *p, int level){
    if(p!=NULL){
        for (int i=0;i<=level;++i)
            printf(" ");
        printf("%2.2d\n", p->id);
        preorder(p->left, level+1);
        preorder(p->right, level+1);
    }
}

void inorder(NodeT *p, int level){
    if (p!=NULL){
        inorder(p->left, level+1);
        for (int i=0;i<=level;++i)
            printf(" ");
        printf("%2.2d\n", p->id);
        inorder(p->right, level+1);
    }
}

void postorder(NodeT *p, int level){
    if (p!=NULL){
        postorder(p->left, level+1);
        postorder(p->right, level+1);
        for (int i=0;i<=level;++i)
            printf(" ");
        printf("%2d.2d\n", p->id);
    }
}

NodeT *createBinTree(int branch, NodeT *parent){   //nodes are read in preorder
    NodeT *p;
    int id;

    if (branch==0)
        printf("Root identifier [0 to end] =");
    else
    if (branch==1)
        printf("Left child of %d [0 to end] =", parent->id);
    else
        printf("Right child of %d [0 to end] =" , parent->id);
    scanf("%d", &id);
    if (id==0)
        return NULL;
    else {
        p=(NodeT *)malloc(sizeof(NodeT));
        if (p==NULL)
            fatalError("out of space in createBinTree");
        p->id=id;
        p->left=createBinTree(1, p);
        p->right=createBinTree(2, p);
        }
    return p;
}

void subtreeInterchange(NodeT *p, int level, int node_key){
      if (p!=NULL){
        if (p->id==node_key){
            NodeT *aux;
            aux=p->left;
            p->left=p->right;
            p->right=aux;
            return;
        }
        subtreeInterchange(p->left, level+1, node_key);
        subtreeInterchange(p->right, level+1, node_key);
    }
}

int max(int a, int b){
    if (a>b)
        return a;
    return b;
}

int treeHeight(NodeT *p){
    if (p==NULL)
        return 0;
    else{
        int left_h=treeHeight(p->left);
        int right_h=treeHeight(p->right);
        return max(left_h, right_h)+1;
    }
}

int nrLeaves(NodeT *root){
    if (root==NULL)
        return 0;
    if (root->left==NULL && root->right==NULL)
        return 1;
    return nrLeaves(root->left)+nrLeaves(root->right);
}

int main()
{
    NodeT *root=createBinTree(0, NULL);
    int node_key;
    printf("node key to interchange subtrees: ");
    scanf("%d", &node_key);
    subtreeInterchange(root, 0, node_key);
    printf("\n");
    preorder(root, 0);
    int tree_h=treeHeight(root);
    printf("\ntree height: %d\n", tree_h);
    int nr_leaves=nrLeaves(root);
    printf("nr of leaves: %d\n", nr_leaves);

    return 0;
}
