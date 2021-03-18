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
void preorder( NodeT *p, int level,char *argv)
{
    FILE *g = fopen(argv, "a");
  if ( p != NULL )
  {
    for ( int i = 0; i <= level; i++ ) fprintf(g, " " ); /* for nice listing */
    fprintf(g, "%2.2d\n", p->id );
    preorder( p->left, level + 1,argv );
    preorder( p->right, level + 1,argv );
  } fclose(g);
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
void inorder( NodeT *p, int level, char *argv )
{
    FILE *g = fopen(argv, "a");
  if ( p != NULL )
  {
    inorder( p->left, level + 1 ,argv);
    for ( int i = 0; i <= level; i++ ) fprintf(g, " " ); /* for nice listing */
        fprintf(g, "%2.2d\n", p->id );
    inorder( p->right, level + 1,argv );
  } fclose(g);
}
//-----  --- Code part 04 ----------------------
// Construction and traversals of binary trees (continued)}
void postorder( NodeT *p, int level, char *argv )
{
  FILE *g = fopen(argv, "a");

  if ( p != NULL )
  {
    postorder( p->left, level + 1 ,argv);
    postorder( p->right, level + 1 ,argv);
    for ( int i = 0; i <= level; i++ ) fprintf(g, " " ); /* for nice listing */
    fprintf(g, "%2.2d\n", p->id );
  } fclose(g);
}
NodeT *createBinTree( int branch, NodeT *parent, char *argv  )
{
  NodeT *p;
  int id;
  FILE *f = fopen(argv, "r");

  /* read node id */
  /*
  if ( branch == 0 )
     printf( "Root identifier [0 to end] =" );
  else
  if ( branch == 1 )
     printf( "Left child of %d [0 to end] =",
              parent->id );
  else
     printf( "Right child of %d [0 to end] =",
              parent->id );
              */
  fscanf(f,"%d", &id);
  if ( id == 0 )
    return NULL;
  else
  { /* build node pointed to by p */
    p = ( NodeT *)malloc(sizeof( NodeT ));
    if ( p == NULL )
      fatalError( "Out of space in createBinTree" );
    /* fill in node */
    p->id = id;
    p->left = createBinTree( 1, p ,argv);
    p->right = createBinTree( 2, p ,argv);
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



int main(int argc, char *argv[])
{
  FILE *f = fopen(argv[1], "r");
  FILE *g = fopen(argv[2], "a");
  NodeT *root;

  root = createBinTree( 0, NULL, argv[1] );
  int targetid;
  fscanf(f,"%d", &targetid);


/**
// these could be left to check the tree before interchanging
  while ('\n' != getc(stdin));
  printf( "\nPreorder listing\n" );
  preorder( root, 0 );
  printf( "Press Enter to continue." );
  while ('\n' != getc(stdin));

**/
  //fprintf(g,"height is %d\n", height(root));
  //fprintf(g,"number of leaves is %d\n", nrLeaves(root));
  interchange(root, 0, targetid);

  //while ('\n' != getc(stdin));
  fprintf(g, "\nPreorder listing\n" );
  preorder( root, 0,argv[2] );
 // fprintf(g, "Press Enter to continue." );
 // while ('\n' != getc(stdin));
  fprintf(g, "\nInorder listing\n" );
  inorder( root, 0,argv[2]);
 // printf( "\n" );
 // while ('\n' != getc(stdin));
  fprintf(g, "\nPostorder listing\n" );
  postorder( root, 0,argv[2] );
  //printf( "\n" );
  //while ('\n' != getc(stdin));
  fclose(f);
  fclose(g);
  return 0;
}
