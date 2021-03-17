#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    char id;
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
    for ( int i = 0; i <= level; i++ ) printf( " " );
    printf( "%c %d\n", p->id, level);
    preorder( p->left, level + 1 );
    preorder( p->right, level + 1 );
    }
}

void inorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
    inorder( p->left, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " );
    printf( "%c %d\n", p->id, level);
    inorder( p->right, level + 1 );
    }
}
void postorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
    postorder( p->left, level + 1 );
    postorder( p->right, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " );
    printf( "%c %d\n", p->id, level);
    }
}
NodeT *createBinTree()
{
    NodeT *p;
    char c;
    /* read node id */
    scanf("%c", &c);
    if ( c == '*' )
    return NULL;
    else
    {
    p = ( NodeT *) malloc( sizeof( NodeT ));
    if ( p == NULL )
    fatalError( "Out of space in createBinTree" );
    p->id = c;
    p->left = createBinTree();
    p->right = createBinTree();
    }
    return p;
}
int nrLeaves( NodeT *p)
{
    if(p == NULL) return 0;
    else if((p->left == NULL) && (p->right == NULL))
        return 1;
    return nrLeaves(p->left) + nrLeaves(p->right);
}
int depth(NodeT *p)
{
    int d, dl, dr;
    if(p == NULL) return 0;
    else
    {
        dl = depth(p->left);
        dr = depth(p->right);
        if(dl > dr) d = dl + 1;
        else d  = dr + 1;
    }
    return d;
}
void interchange(NodeT *p)
{
    NodeT *change;
    if(p == NULL) return 0;
    else
    {
    change = p->left;
    p->left = p->right;
    p->right = change;
    }

}
NodeT *findKeyLeft(NodeT *p, char key)
{
    if(p == NULL) return 0;
        else if((int)p->id == (int)key) return p;
                else if(p->left != NULL) return findKeyLeft(p->left, key);
}

NodeT *findKeyRight(NodeT *p, char key)
{

    if(p == NULL) return 0;
        else if((int)p->id == (int)key) return p;
                else if(p->right != NULL) return findKeyRight(p->right, key);
}
NodeT *findKey(NodeT *p, char key)
{
    NodeT *leftSub, *rightSub;
    leftSub = findKeyLeft(p, key);
    rightSub = findKeyRight(p, key);

    if(leftSub != NULL) return leftSub;
    else if(rightSub != NULL) return rightSub;
}


int main()
{
    int nr;
    NodeT *root = createBinTree();
    //printing the tree in preorder, inorder, postorder
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

    //counting the leaves and the depth of the tree
    nr = nrLeaves(root);
    printf("Number of leaves: %d \n", nr);
    printf("The tree's depth: %d \n", depth(root));

    //the user inputs a node ID, interchange the subtrees after the given node
    char k;
    printf("choose a node: ");
    scanf("%s", &k);
    printf( "\nInterchanging the subtree after the given node:\n" );
    NodeT *node = findKey(root, k);
    interchange(node);
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
    return 0;
}
