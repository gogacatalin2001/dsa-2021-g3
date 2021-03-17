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
        printf( "Root identifier [0 to end] = " );
    else if ( branch == 1 )
        printf( "Left child of %d [0 to end] = ",
                parent->id );
    else
        printf( "Right child of %d [0 to end] = ",
                parent->id );
    scanf("%d", &id);
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
        p->left = createBinTree( 1, p );
        p->right = createBinTree( 2, p );
    }
    return p;
}

void interchange(NodeT *root)
{
    if (root == NULL)
        return;

    // we change from leaves to the root
    interchange(root->left);
    interchange(root->right);

    // interchanging the right and left subtrees
    NodeT *p = root->left;
    root->left = root->right;
    root->right = p;
}

int height(NodeT *root)
{
    if (root->left == NULL && root->right == NULL)
        return 0; // if leaf return
    int hleft = 0, hright = 0;

    if (root->left != NULL)
        hleft = height(root->left); // if the left side exists, we find the height

    if (root->right != NULL)
        hright = height(root->right); // if the right side exists, we find the height

    if (hleft > hright) // we return the side that has the greater height
        return 1 + hleft;
    return 1 + hright;
}

int nrleafs(NodeT *root)
{
    if (root->left == NULL && root->right == NULL)
        return 1; // if leaf return

    int nrlright = 0, nrlleft = 0;

    if (root->right != NULL)
        nrlright = nrleafs(root->right); // if there exists nodes in the left side, then there exists leaves

    if (root->left != NULL)
        nrlleft = nrleafs(root->left); // if there exists nodes in the right side, then there exists leaves

    return nrlright + nrlleft;
}

int main()
{
    NodeT *root = createBinTree( 0, NULL );
    while ('\n' != getc(stdin));

    printf( "\nPreorder listing\n" );
    preorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));

    printf( "\nInorder listing\n" );
    inorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));

    printf( "\nPostorder listing\n" );
    postorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));

    interchange(root);

    printf( "\nInterchanged tree preorder listing\n" );
    preorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));

    printf( "\nInterchanged tree inorder listing\n" );
    inorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));

    printf( "\nInterchanged tree postorder listing\n" );
    postorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));

    printf( "\nHeight of the tree: %d\nPress Enter to continue.", height(root) );
    while ('\n' != getc(stdin));

    printf( "\nNumber of leafs in the tree: %d\nPress Enter to continue.", nrleafs(root) );
    while ('\n' != getc(stdin));
    return 0;
}
