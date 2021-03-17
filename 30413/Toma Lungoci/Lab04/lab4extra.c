#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i=0;
float sum=0, arr[100];

typedef struct node
{
    int id;
    struct node *left, *right;
}NodeT;

NodeT *createBinTree( int branch, NodeT *parent )
{
    NodeT *p;
    int id;
    /* read node id */
    if ( branch == 0 )
        printf( "Root identifier [0 to end] =" );
    else if ( branch == 1 )
        printf( "Left child of %d [0 to end] =",
                parent->id );
    else
        printf( "Right child of %d [0 to end] =",
                parent->id );
    scanf("%d", &id);
    if ( id == 0 )
        return NULL;
    else
    {
        p = ( NodeT *)malloc(sizeof( NodeT ));
        p->id = id;
        p->left = createBinTree( 1, p );
        p->right = createBinTree( 2, p );
    }
    return p;
}

int isEmpty(NodeT *p)
{
    if(p->left==NULL && p->right==NULL)
        return 1;
    return 0;
}
NodeT *find (char id, NodeT *root)
{
    if(root->id==id)
        return root;
    else if(root==NULL)
        return;
    else
    {
        find(id, root->left);
        find(id, root->right);
    }
}
void interchange(char id, NodeT *root)
{
    NodeT *q=find(id,root);
        NodeT *aux=NULL;
        aux=q->left;
        q->left=q->right;
        q->right=aux;
}

void Teams(NodeT*p)
{
    int count=0;
    if(p!=NULL)
    {
        Teams(p->left);
        Teams(p->right);
        count++;
        sum=sum+p->id;
        if(isEmpty(p)!=1)
        {
            arr[i++]=sum/count; //I have a global sum and count, and each time i "reach" a node the 3rd time
				// (postorder) I compute the average, store it into an array and continuie with the next.
        }
    }
}

float maxInArray(float arr[])
{
    int max=arr[0];
    int i=1;
    while(arr[i++]!=0)
    {
        if(arr[i]>max)
        {
            max=arr[i];
        }
    }
    return max;
}

int main()
{
    NodeT *root = createBinTree( 0, NULL );
    Teams(root);
    float BestTeam=maxInArray(arr);//the best average should be the maximumof the average array
    printf("%f", BestTeam);



    return 0;
}
