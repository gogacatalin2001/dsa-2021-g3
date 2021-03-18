#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    int id;             /// id = number of months
    double sum;            /// sum of all ids of employees working below and including the id of this node
    struct node_type *left, *right;
} NodeT;

NodeT *createBinTree(FILE *fileI) /// returns root
{
    NodeT *p;
    int n;
    fscanf(fileI, "%d", &n);
    if (n == -1) {
        return NULL;
    }
    else {
        p = (NodeT *) malloc(sizeof(NodeT));
        if (p == NULL) {
            printf("out of space in createBinTree");
            exit(1);
        }
        p->id = n;
        p->left = createBinTree(fileI);
        p->right = createBinTree(fileI);
    }
    return p;
}

double computeSum (NodeT *p)   /// this function computes sum of tenures of the node and everything below it
{                           /// for every node in the tree and puts it in <node>->sum
    if (p->left == NULL && p-> right == NULL) {
        p->sum = p->id;
        return p->sum;
    }
    p->sum = computeSum(p->left) + computeSum(p->right) + p->id;
    return p->sum;
}

int countEmployees(NodeT *p, double *max)    /// number of employees working below the node + 1
{
    int employees;
    if (p->left == NULL && p->right == NULL) {
        employees = 0;
        return 1;
    }
    employees = 1 + countEmployees(p->left, max) + countEmployees(p->right, max);
    p->sum = p->sum / employees;         /// now in sum we have the average tenure we are looking for
    if (p->sum > *max) {
        *max = p->sum;              /// in the address pointed to by pointer max will be saved the maximum
    }                               /// average tenure
    return employees;
}

NodeT *returnMax (double max, NodeT *p) /// returns the node with sum == max
{
    if (p->left == NULL && p->right == NULL) {
        return NULL;
    }
    if (p->sum == max) {
        return p;
    }
    returnMax(max, p->left);
    returnMax(max, p->right);
}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    NodeT *root = createBinTree(fileI);

    double max = 0;

    computeSum(root);
    countEmployees(root, &max);

    NodeT *rootBestTeam = returnMax(max, root);

    printf("%lf\n", max);
    printf("%d", rootBestTeam->id);
    return 0;
}
