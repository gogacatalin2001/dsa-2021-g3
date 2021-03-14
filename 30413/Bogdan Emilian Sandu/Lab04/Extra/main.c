#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int time;
    struct node *left,*right;
}NodeT;

NodeT *manager;//variabila globala
NodeT *createBinTree();
float highestTenure(NodeT *root,int *nr);
NodeT *highestTenureM(NodeT *root,float *maxi);
NodeT *highestTenureFinal(NodeT *root);

int main()
{
    NodeT *root=createBinTree();
    NodeT *manager;
    manager=highestTenureFinal(root);
    printf("%p %d",manager, manager->time);
    return 0;
}

NodeT *highestTenureFinal(NodeT *root)//condenseaza toate functiile anterioare intr-o singura functie
{
    manager=root;
    float maximum=0;
    manager=highestTenureM(root,&maximum);
    return manager;
}
NodeT *highestTenureM(NodeT *root,float *maxi)//parcurge nodurile si calculeaza media aritmetica a fiecarui subtree ce are ca root nodul parcurs; omite frunzele
{
    if(root==NULL || (root->left==NULL && root->right==NULL)) return;
    int nr;
    float sum;
    nr=0;
    sum=highestTenure(root,&nr);
    sum=sum/nr;
    if(sum>(*maxi))
        {
            *maxi=sum;
            manager=root;
        }
    highestTenureM(root->left,maxi);
    highestTenureM(root->right,maxi);
    return manager;
}
float highestTenure(NodeT *root,int *nr)//calculeaza nr de noduri dintr-un subtree si suma nodurilor sale
{
    if(root==NULL) return 0;
    *nr=*nr+1;
    return root->time+highestTenure(root->left,nr)+highestTenure(root->right,nr);
}
NodeT *createBinTree()
{
    NodeT *p;
    int d;
    scanf("%d",&d);
    if(d==-1) return NULL;
    p=(NodeT*)malloc(sizeof(NodeT));
    if(p==NULL) exit(1);
    p->time=d;
    p->left=createBinTree();
    p->right=createBinTree();
    return p;
}
