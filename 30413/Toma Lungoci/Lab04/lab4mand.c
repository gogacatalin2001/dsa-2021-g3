#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    char id;
    struct node_type *left, *right;
}NodeT;

void preorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
        preorder( p->left, level + 1 );
        preorder( p->right, level + 1 );
    }
}
void inorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        inorder( p->left, level + 1 );
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
        inorder( p->right, level + 1 );
    }
}
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
            /* build node pointed to by p */
            p = ( NodeT *)malloc(sizeof( NodeT ));
            /* fill in node */
            p->id = id;
            p->left = createBinTree( 1, p );
            p->right = createBinTree( 2, p );
        }
        return p;
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
int isEmpty(NodeT *p)
{
    if(p->left==NULL && p->right==NULL)
        return 1;
    return 0;
}
int height(NodeT* p)
{
    if (p == NULL)
        return 0;
    else {

        int l = height(p->left);
        int r = height(p->right);
        if (l > r)
            return (l + 1);
        else
            return (r + 1);
    }
}

int main()
{
    NodeT *root = createBinTree( 0, NULL );
    printf( "\nPreorder listing\n" );
    preorder( root, 0 );
    printf( "\nInorder listing\n" );
    inorder( root, 0 );
    printf( "\nPostorder listing\n" );
    postorder( root, 0 );
    interchange(1, root);
    printf("-------------------------\n");
    preorder(root, 0);
    int h=height(root);
    printf("\n\n%d\n", h);
    return 0;
}
