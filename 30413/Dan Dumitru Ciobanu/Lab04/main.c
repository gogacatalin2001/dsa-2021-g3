#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int id;
  struct Node *left, *right;
} NodeT;

void preorder( NodeT *p, FILE *fo )
{
  if ( p != NULL )
    {
        fprintf( fo," %d", p->id );
        preorder( p->left,fo );
        preorder( p->right,fo );
    }
}
void inorder( NodeT *p, FILE *fo )
{
  if ( p != NULL )
    {
        inorder( p->left ,fo);
        fprintf( fo," %d", p->id );
        inorder( p->right,fo );
    }
}

void postorder( NodeT *p, FILE *fo )
{
  if ( p != NULL )
    {
        postorder( p->left,fo);
        postorder( p->right,fo );
        fprintf( fo," %d", p->id );
    }
}

void swap( NodeT *p )
{
    NodeT *temp;
    temp = p->left;
    p->left = p->right;
    p->right = temp;
}

NodeT *createBinaryTree( FILE *ff )
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
        {
            printf("ERROR");
            exit(1);
        }
        p->id = id;
        p->left = createBinaryTree(ff);
        p->right = createBinaryTree(ff);
        }
    return p;
}

int nrLeaves( NodeT *root )
{
    if(root==0)
        return 0;
    if(root->left==NULL && root->right==NULL)
        return 1;
    return nrLeaves(root->left)+nrLeaves(root->right);
}

int heightOfTree( NodeT *root )
{

    if(root==NULL) return 0;
    if(heightOfTree(root->left)<heightOfTree(root->right))
        return heightOfTree(root->right)+1;
        else return heightOfTree(root->left)+1;


}

NodeT* searchByKey( NodeT* root, int key )
{
    if(root==NULL)
        return 0;
    if(root->id==key)
        return root;
    if(root->right!=NULL)
        searchByKey(root->right,key);
    if(root->left!=NULL)
        searchByKey(root->left,key);
}


int main( int argc, char *argv[] )
{
    FILE *ff=fopen(argv[1],"r");
    FILE *fo=fopen(argv[2],"w");

    NodeT *root=createBinaryTree(ff);
    NodeT *p;
    int key;

    fprintf(fo, "In the tree there are %d leaves.\n", nrLeaves(root));
    fprintf(fo, "The height is %d.\n", heightOfTree(root));

    fscanf(ff,"%d",&key);
    p=searchByKey(root,key);

    if(p!=0)
        swap(p);
    else
        printf("The key was not found!");

    fprintf(fo,"Inorder: ");
    inorder(root,fo);
    fprintf(fo,"\n");

    fprintf(fo,"Preorder: ");
    preorder(root,fo);
    fprintf(fo,"\n");

    fprintf(fo,"Postorder: ");
    postorder(root,fo);
    fprintf(fo,"\n");

    return 0;
}
