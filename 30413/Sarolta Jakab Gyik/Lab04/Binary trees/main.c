/*Modify the supplied code and add functions to:
• Interchange the left and right subtrees of a given node.
Output the traversals of the new tree in preorder,
inorder and postorder.
• Determine the height of a binary tree, Output: height as a number.
• Determine the number of leaves in a binary tree.
Output: number of leaves */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_type
{
    char id;
    struct node_type *left, *right;
} NodeT;
NodeT *createBinTree()
{
    NodeT *p;
    char c;
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
        for ( int i = 0; i <= level; i++ )
            printf( " " );
        printf( "%c\n", p->id );
        preorder( p->left, level + 1 );
        preorder( p->right, level + 1 );
        //printf("The level is:%d", level);
    }
}
void inorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        inorder( p->left, level + 1 );
        for ( int i = 0; i <= level; i++ )
            printf( " " );
        printf( "%c\n", p->id );
        inorder( p->right, level + 1 );
    }
}
void postorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        postorder( p->left, level + 1 );
        postorder( p->right, level + 1 );
        for ( int i = 0; i <= level; i++ )
            printf( " " );
        printf( "%c\n", p->id );
    }
}
int nrLeaves(NodeT *root)
{
    if(root == NULL)
        return 0;
    if((root->left == NULL) && (root->right == NULL))
        return 1;
    else return nrLeaves(root->left)+nrLeaves(root->right);
}
int heightTree(NodeT *root)
{
    int max, maxLeft, maxRight;
    if(root == NULL)
        return 0;
    else
    {
        maxLeft = heightTree(root->left);
        maxRight = heightTree(root->right);
        if(maxLeft > maxRight)
            max = maxLeft +1;
        else max = maxRight +1;
    }
    return max;
}
void interchangeSubtrees(NodeT *p)
{
    if(p != NULL && (p->left != NULL || p->right != NULL))
    {
        NodeT *change;
        change = p->left;
        p->left = p->right;
        p-> right = change;
    }
}
NodeT *findNode(char id, NodeT *root)
{
    if(root != NULL)
    {
        if((int)id == (int)root->id)
            return root;
        NodeT *leftNode = findNode(id, root->left);
        if(leftNode)
            return leftNode;
        NodeT *rightNode = findNode(id, root->right);
        if(rightNode)
            return rightNode;
    }
    else return NULL;
}
int main()
{
    printf("Introduce a binary tree:");
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
    int x = nrLeaves(root);
    printf("The nr of leaves:%d", x);
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));
    x = heightTree(root);
    printf("The height of the tree:%d", x);
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));
    interchangeSubtrees(root);
    preorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));
    inorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));
    postorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));
    printf("Introduce a node:");
    char id;
    scanf("%s", &id);
    NodeT *p;
    p = findNodeBoth(id, root);
    preorder( root, 0 );
    //printf("\n%c\n\n", p->id);
    if(p == NULL)
        printf("This node was not found in the bin tree\n");
    else interchangeSubtrees(p);
    preorder( root, 0 );
    printf( "Press Enter to continue." );
    while ('\n' != getc(stdin));
    return 0;
}
