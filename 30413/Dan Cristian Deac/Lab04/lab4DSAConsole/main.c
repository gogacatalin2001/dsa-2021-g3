#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
  char id; /* node name */
  /* ... other useful info */
  struct node_type *left, *right;
} NodeT;
void fatalError( const char *msg )
{
 printf( msg );
 printf( "\n" );
 exit ( 1 );
}
void preorder( NodeT *p, int level)
{
  if ( p != NULL )
  {
    for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
    printf( "%2.2d\n", p->id );
    preorder( p->left, level + 1 );
    preorder( p->right, level + 1);
  }
}
void interchange( NodeT *p, int level, int TargetId)
{
  if ( p != NULL )
  {
    if(p->id == TargetId)
    {
      NodeT *q = p->left;
      p->left = p->right;
      p->right = q;
      //printf("success");
      return;
    }

    interchange( p->left, level + 1, TargetId );
    interchange( p->right, level + 1, TargetId );
  }

}
void inorder( NodeT *p, int level)
{
  if ( p != NULL )
  {
    inorder( p->left, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
    inorder( p->right, level + 1 );
  }
}
//-----  --- Code part 04 ----------------------
// Construction and traversals of binary trees (continued)}
void postorder( NodeT *p, int level )
{


  if ( p != NULL )
  {
    postorder( p->left, level + 1 );
    postorder( p->right, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
    printf( "%2.2d\n", p->id );
  }
}
NodeT *createBinTree( int branch, NodeT *parent  )
{
  NodeT *p;
  int id;


  /* read node id */

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


int nrLeaves( NodeT *p )
{
  if ( p != NULL )
  {

    if(nrLeaves( p->left ) == 0 && nrLeaves( p->right ) == 0)
        return 1;
    return nrLeaves(p->right) + nrLeaves(p->left);
  } return 0;
}


int height( NodeT *p )
{
  if ( p != NULL )
  {

    if(height( p->left ) >  height( p->right ))
        return height(p->left) +1;
    else return height(p->right) + 1;
  } return 0;
}



int main()
{
  NodeT *root;

  root = createBinTree( 0, NULL);
  int targetid;
  printf("the Target node for swapping: ");
  scanf("%d", &targetid);


/**
// these could be left to check the tree before interchanging
  while ('\n' != getc(stdin));
  printf( "\nPreorder listing\n" );
  preorder( root, 0 );
  printf( "Press Enter to continue." );
  while ('\n' != getc(stdin));

**/
  printf("height is %d\n", height(root));
  printf("number of leaves is %d\n", nrLeaves(root));
  interchange(root, 0, targetid);

  while ('\n' != getc(stdin));
  printf( "\nPreorder listing\n" );
  preorder( root, 0 );
  printf( "Press Enter to continue." );
  while ('\n' != getc(stdin));
  printf( "\nInorder listing\n" );
  inorder( root, 0);
  printf( "Press Enter to continue.");
  while ('\n' != getc(stdin));
  printf( "\nPostorder listing\n" );
  postorder( root, 0);
  printf( "Press Enter to continue.");
  while ('\n' != getc(stdin));

  return 0;
}
