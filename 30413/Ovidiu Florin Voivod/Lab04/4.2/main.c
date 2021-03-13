#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    int id; /* node name */
    //label ; /* appropriate type for label */
    struct node_type *left, *right;
} NodeT;
void fatalError( const char *msg )
{
    printf( msg );
    printf( "\n" );
    exit ( 1 );
}

NodeT *createBinTree( int branch, NodeT *parent, FILE *pf)
{
    NodeT *p;
    int id;

    /* read node id */
    /*if ( branch == 0 )
        printf( "Root identifier [0 to end] =" );
    else if ( branch == 1 )
        printf( "Left child of %d [0 to end] =",
                parent->id );
    else
        printf( "Right child of %d [0 to end] =",
                parent->id );*/
    fscanf(pf,"%d", &id);
    if ( id == 0 )
        return NULL;
    else
    {
        /* build node pointed to by p */
        p = ( NodeT *)malloc(sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Out of space in createBinTree" );
        /* fill in node */
        p->id = id;
        p->left = createBinTree( 1, p,pf );
        p->right = createBinTree( 2, p,pf );
    }
    return p;
}


///Nr of leaves of a binary tree
int nrLeaves(NodeT *root)
{
    if(root->left==NULL && root->right==NULL) return 1;
    return nrLeaves(root->left)+nrLeaves(root->right);
}
///Height in a binary tree
int TreeHeight(NodeT *root)
{
    int left,right;
    if(root==NULL) return 0;

    right=TreeHeight(root->right);
    left=TreeHeight(root->left);

    if(left>right) return TreeHeight(root->left)+1;
    else return TreeHeight(root->right)+1;


}
///Function to interchange left-right subtrees of a node
void interchange(NodeT *nodePtr)
{
    NodeT *aux;
    aux=nodePtr->right;
    nodePtr->right=nodePtr->left;
    nodePtr->left=aux;
}

void preorder( NodeT *p, int level, FILE *pr)
{
    if ( p != NULL )
    {
        for ( int i = 0; i <= level; i++ ) fprintf( pr," " ); /* for nice listing */
        fprintf( pr,"%2.2d\n", p->id );
        preorder( p->left, level + 1,pr );
        preorder( p->right, level + 1,pr );
    }
}
void inorder( NodeT *p, int level, FILE *pr )
{
    if ( p != NULL )
    {
        inorder( p->left, level + 1,pr );
        for ( int i = 0; i <= level; i++ ) fprintf( pr," " ); /* for nice listing */
        fprintf(pr,"%2.2d\n", p->id );
        inorder( p->right, level + 1,pr );
    }
}

void postorder( NodeT *p, int level, FILE *pr)
{
  if ( p != NULL )
  {
    postorder( p->left, level + 1,pr );
    postorder( p->right, level + 1,pr );
    for ( int i = 0; i <= level; i++ ) fprintf(pr," " ); /* for nice listing */
    fprintf(pr,"%2.2d\n", p->id );
  }
}

NodeT* Search( NodeT *p,int key )
{
    NodeT *pr,*pl;
    if ( p==NULL ) return 0;
    if(p->id==key) return p;
    if(p->right!=NULL) Search(p->right,key);
    if(p->left!=NULL)  Search(p->left,key);


    /*pr=Search(p->right,key);
    if(pr!=NULL) return pr;
    pl=Search(p->left,key);
    if(pl!=NULL) return pl;*/

}

int main(int argc, char **argv)
{
    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen(argv[2],"w");
    NodeT *root=createBinTree(0,NULL,fin);
    NodeT *find;
    int key;

    fprintf(fout,"Number of leaves in the binary tree rooted in %d is: %d\n",root->id,nrLeaves(root));
    fprintf(fout,"Height of the binary tree rooted in %d is: %d\n",root->id,TreeHeight(root));
    //fprintf(fout,"\nWrite node of whose subgraphs to interchange:");
    fscanf(fin,"%d",&key);
    find=Search(root,key);
    interchange(find);
    fprintf(fout,"Preorder listing with interchanged subtrees\n");
    preorder(root,0,fout);
    fprintf(fout,"\nInorder listing with interchanged subtrees\n");
    inorder(root,0,fout);
    fprintf(fout,"\nPostorder listing with interchanged subtrees\n");
    postorder(root,0,fout);
    return 0;
}
