#include <stdio.h>
#include <stdlib.h>
/// node type
typedef struct node_type
{
    int months;
    struct node_type *left, *right;
} NodeT;
/// contains the total number of months and the number of people in a team
typedef struct sol_type
{
    double sum;
    int cnt;
} SolT;
/// error message
void fatalError(const char *msg, int i)
{
    printf( msg );
    printf( "\n" );
    exit ( i );
}
/// open file
FILE *openCheck (const char *path, const char *mode)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        fatalError ("Cannot open the file", 1);
    }
    return pf;
}
/// create a binary tree
NodeT *createBinTree( int branch, NodeT *parent, FILE *in)
{
  NodeT *p;
  int months;
  fscanf(in, "%d", &months);
  if ( months == 0 )
    return NULL;
  else
  { /* build node pointed to by p */
    p = ( NodeT *)malloc(sizeof( NodeT ));
    if ( p == NULL )
      fatalError( "Out of space in createBinTree", 2 );
    /* fill in node */
    p->months = months;
    p->left = createBinTree( 1, p, in );
    p->right = createBinTree( 2, p, in );
  }
  return p;
}
///---functions---------------------------------------------------------------------------------------
double maxAverage = 0.0; ///set maxAverage to 0
NodeT *p = NULL; ///set the pointer to the oldest team's manager to NULL
/// here we fill a struct which contains the sum and the no. of nodes for a certain manager
SolT *createAndFill(double sum, int cnt)
{
    SolT *p = (SolT *)malloc(sizeof(SolT));
    if (p)
    {
        p -> sum = sum;
        p -> cnt = cnt;
    }
    return p;
}
///---this is the function which helps us to find the maximal average
SolT *needForAverage (NodeT *root)
{
    SolT *sol;
    if (root == NULL)
    {
        sol = createAndFill(0.0,0); ///at the beginning sum and count must be 0, from that on we calculate the average
        return sol;
    }
    SolT *left = needForAverage(root->left); ///solve for left subtree
    SolT *right = needForAverage(root->right); ///solve for right subtree
    sol = createAndFill(root->months + left->sum + right->sum,1 + left->cnt + right->cnt);
    ///this is what the line above does:
    /*sol->sum = root->months + left->sum + right->sum;
    sol->cnt = 1 + left->cnt + right->cnt;*/
    double localAverage = sol->sum / sol->cnt; ///we calculate a local average and than compare it
    if (localAverage > maxAverage && (root->left != NULL || root->right != NULL)) ///leaves cannot be managers
    {
        maxAverage = localAverage;
        p = root;
    }
    return sol;
}
///---this is the function which takes as argument the root(CEO)
///---and returns the node which has the oldest team
NodeT *findManagerWithHighestTenure (NodeT *root)
{
    needForAverage(root);
    return p;
}
///---------------------------------------------------------------------------------------------------
int main()
{
    ///here I open a file which contains the binary tree from the example
    FILE *in = openCheck("in.txt", "r");
    NodeT *root = createBinTree( 0, NULL, in);
    NodeT *manager = findManagerWithHighestTenure(root); ///call the function and get the manager with oldest team
    printf("%d", manager->months); ///print the number of months the manager has spent at the company
    return 0;
}
