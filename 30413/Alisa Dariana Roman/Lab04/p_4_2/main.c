#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    char id;
    struct node_type *left, *right;
} NodeT;

NodeT *createBinTree(FILE *fileI) /// invoked as: root = createBinTree();
{
    NodeT *p;
    char c;
    fscanf(fileI, "%c", &c);
    if(c == '*') {
        return NULL;
    }
    else {
        p = (NodeT*) malloc(sizeof(NodeT));
        if(p == NULL) {
            printf("error: out of space in createBinTree");
            exit(1);
        }

        p->id = c;
        p->left = createBinTree(fileI);
        p->right = createBinTree(fileI);
    }
    return p;
}

void preorder(NodeT *p, int level, FILE *fileO)
{
    int i;
    if(p != NULL) {
        for(i = 0; i <= level; i++) {
            fprintf(fileO, "  ");
        }
        fprintf(fileO, "%2.2c\n", p->id);
        preorder(p->left, level + 1, fileO);
        preorder(p->right, level + 1, fileO);
    }
}

void inorder(NodeT *p, int level, FILE *fileO)
{
    int i;
    if(p != NULL) {
        inorder(p->left, level + 1, fileO);
        for(i = 0; i <= level; i++) {
            fprintf(fileO, "  ");
        }
        fprintf(fileO, "%2.2c\n", p->id);
        inorder(p->right, level + 1, fileO);
    }
}

void postorder(NodeT *p, int level, FILE *fileO)
{
    int i;
    if(p != NULL) {
        postorder(p->left, level + 1, fileO);
        postorder(p->right, level + 1, fileO);
        for(i = 0; i <= level; i++) {
            fprintf(fileO, "  ");
        }
        fprintf(fileO, "%2.2c\n", p->id);
    }
}

void displayAllTraversals(NodeT *root, FILE *fileO)
{
    fprintf(fileO, "preorder:\n");
    preorder(root, 0, fileO);
    fprintf(fileO, "inorder:\n");
    inorder(root, 0, fileO);
    fprintf(fileO, "postorder:\n");
    postorder(root, 0, fileO);
}

void interchangeSubtrees(NodeT* root)
{
    NodeT *aux;
    aux = root->left;
    root->left = root->right;
    root->right = aux;
}

int computeMax(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

int computeHeight(NodeT* p)
{
    if(p == NULL) {
        return 0;
    }
    int left = computeHeight(p->left);
    int right = computeHeight(p->right);
    return ( computeMax(left, right) + 1 );
}

int countLeaves(NodeT *p)
{
    if(p == NULL) {
        return 0;
    }
    if(p->left == NULL && p->right == NULL) {
        return 1;
    }
    else {
        return ( countLeaves(p->left) + countLeaves(p->right) );
    }
}


int main(int argc, int *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");
    NodeT *root = createBinTree(fileI);

    fprintf(fileO, "before interchange of subtrees:\n");
    displayAllTraversals(root, fileO);

    fprintf(fileO, "after interchange of subtrees:\n");
    interchangeSubtrees(root);
    displayAllTraversals(root, fileO);

    fprintf(fileO, "height is: %d\n", computeHeight(root));

    fprintf(fileO, "number of leaves is: %d\n", countLeaves(root));
    return 0;
}
