#include <stdio.h>
#include <stdlib.h>


#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


typedef struct node_type
{
  int id;

  struct node_type *left, *right;
} NodeT;


void fatalError( const char *msg )
{
 printf( msg );
 printf( "\n" );
 exit ( 1 );
}


void preorder( NodeT *p)
{
    if ( p == NULL ) return;

    printf( "%d \n", p->id );
    preorder( p->left);
    preorder( p->right);

}


NodeT *createBinTree( int branch, NodeT *parent )
{
  NodeT *p;
  int id;

  if ( branch == 0 )
     printf( "Root identifier [0 to end] =" );
  else
  if ( branch == 1 )
     printf( "Left child of %d [0 to end] =",
              parent->id );
  else
     printf( "Right child of %d [0 to end] =",
              parent->id );
  scanf("%d", &id);
  if ( id == 0 )
    return NULL;
  else
  { /* build node pointed to by p */
    p = ( NodeT *)malloc(sizeof( NodeT ));
    if ( p == NULL )
      fatalError( "Out of space in createBinTree" );
    /* fill in node */
    p->id = id;
    p->left = createBinTree( 1, p );
    p->right = createBinTree( 2, p );
  }
  return p;
}


int nleaves (NodeT *root){

    if(root == NULL)
        return 0;
    if(root->right==NULL && root->left==NULL)
       return 1;
    else
       return nleaves(root->right)+ nleaves(root->left);
}

int tree_height(NodeT *root) {
    if (root == NULL) ///CONDITIA ASTA II SFANTA!!!!!!!
        return 0;
    else {

       int left_height = tree_height(root->left);
       int right_height = tree_height(root->right);


        return max(left_height, right_height) + 1;
 }
}
int main()
{
  NodeT *root;

  root = createBinTree(0, NULL);
  preorder(root);
  while ('\n' != getc(stdin));


  printf("\n%d \n", nleaves(root));

  printf("\n%d \n", tree_height(root));

  return 0;


}
