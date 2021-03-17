#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
  int id;
  struct node_type *left, *right;
} NodeT;

NodeT *createBinTree(FILE *ff)
{
  NodeT *p;
  int id;
  fscanf(ff,"%d", &id);
  if ( id == 0 )
    return NULL;
  else
  {
    p = ( NodeT *) malloc( sizeof( NodeT ));
    if ( p == NULL )
      fatalError( "Out of space in createBinTree" );
    p->id = id;
    p->left = createBinTree(ff);
    p->right = createBinTree(ff);
  }
  return p;
}

void fatalError( const char *msg )
{
 printf( msg );
 printf( "\n" );
 exit ( 1 );
}
void preorder( NodeT *p, FILE *fo)
{
  if ( p != NULL )
  { int i;
    fprintf( fo," %d", p->id );
    preorder( p->left,fo );
    preorder( p->right,fo );
  }
}
void inorder( NodeT *p, FILE *fo )
{
  if ( p != NULL )
  { int i;
    inorder( p->left ,fo);
    fprintf( fo," %d", p->id );
    inorder( p->right,fo );
  }
}

void postorder( NodeT *p, FILE *fo )
{
  if ( p != NULL )
  { int i;
    postorder( p->left,fo);
    postorder( p->right,fo );
    fprintf( fo," %d", p->id );
  }
}

void interchange(NodeT *p)
{
    NodeT *aux;
    aux=p->left;
    p->left=p->right;
    p->right=aux;
}

int nrLeaves(NodeT *root)
{
    if(root==0)return 0;
    if(root->left==NULL && root->right==NULL)
        return 1;
    return nrLeaves(root->left)+ nrLeaves(root->right);
}

 int heightOfTree(NodeT *root)
{

    if(root==NULL) return 0;
    if(heightOfTree(root->left)<heightOfTree(root->right))
            return 1+heightOfTree(root->right);
        else return 1+heightOfTree(root->left);


}
NodeT* searchByKey(NodeT* root, int key)
{
    if(root==NULL)return 0;
    if(root->id==key)
        return root;
    if(root->right!=NULL) searchByKey(root->right,key);
    if(root->left!=NULL) searchByKey(root->left,key);

}


int main(int argc, char **argv)
{   FILE *ff=fopen(argv[1],"r");
    FILE *fo=fopen(argv[2],"w");

    NodeT *root=createBinTree(ff),*p;
    int key;

    fprintf(fo,"There are %d leaves in the given binary tree.\n",nrLeaves(root));
    fprintf(fo,"There height of the given tree is %d.\n",heightOfTree(root));

    fscanf(ff,"%d",&key);
    p=searchByKey(root,key);
    if(p!=0)
        interchange(p);
    else printf("The key was not found!");

    fprintf(fo,"The tree in preorder: ");
    preorder(root,fo);
    fprintf(fo,"\n");
    fprintf(fo,"The tree in inorder: ");
    inorder(root,fo);
    fprintf(fo,"\n");
    fprintf(fo,"The tree in postorder: ");
    postorder(root,fo);
    fprintf(fo,"\n");

    return 0;
}

