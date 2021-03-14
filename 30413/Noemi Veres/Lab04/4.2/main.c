#include <stdio.h>
#include <stdlib.h>
/// node type
typedef struct node_type
{
    char id; /* node name */
    struct node_type *left, *right;
} NodeT;
/// error message
void fatalError(const char *msg, int i)
{
    printf( msg );
    printf( "\n" );
    exit ( i );
}
/// open file
FILE *openCheck (const char *path, const char *mode)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        fatalError ("Cannot open the file", 1);
    }
    return pf;
}
/// create a binary tree
NodeT *createBinTree(FILE *in)
{
    NodeT *p;
    char c; /* read node id */
    fscanf(in, "%c", &c);
    if ( c == '*' )
        return NULL; /* empty tree; do nothing */
    else
    {
        /* build node pointed to by p */
        p = ( NodeT *) malloc( sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Out of space in createBinTree", 2 );
        /* fill in node */
        p->id = c;
        p->left = createBinTree(in);
        p->right = createBinTree(in);
    }
    return p;
}
/// construction of traversals
void preorder(NodeT *p, FILE *out)
{
    if ( p != NULL )
    {
        fprintf(out, "%c ", p->id );
        preorder( p->left, out);
        preorder( p->right, out);
    }
}
void inorder( NodeT *p, FILE *out)
{
    if ( p != NULL )
    {
        inorder( p->left, out);
        fprintf(out, "%c ", p->id );
        inorder( p->right, out);
    }
}
void postorder( NodeT *p, FILE *out)
{
    if ( p != NULL )
    {
        postorder( p->left, out );
        postorder( p->right, out);
        fprintf(out, "%c ", p->id);
    }
}
/// find the given node
NodeT *find(NodeT *p, char c)
{
    if ( p == NULL ) return NULL;
    if (p->id == c) return p;
    NodeT *left = find( p->left,c);
    if (left) return left;
    NodeT *right = find(p->right,c);
    return right;
}
/// Interchange the left and right subtrees of a given node
void interchange (NodeT *root, char c)
{
    NodeT *given = find(root,c);
    if (given->left != NULL || given->right != NULL)
    {
        NodeT *aux = NULL;
        aux = given->left;
        given->left = given->right;
        given->right = aux;
    }
}
/// height of tree
int max (int a, int b)
{
    if (a > b) return a;
    return b;
}
int heightTree (NodeT *root)
{
    if (root == NULL) return 0;
    return 1+max(heightTree(root->left),heightTree(root->right));
}
/// no. of leaves
int nrLeaves (NodeT *root)
{
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return nrLeaves(root->left)+nrLeaves(root->right);
}
int main(int argc, char *argv[])
{
    FILE *in = openCheck("in.txt", "r");
    FILE *out = openCheck("out.txt", "w");
    NodeT *root = createBinTree(in);
    int height = heightTree(root);
    fprintf(out,"height of tree: %d\n", height);
    int leaf_cnt = nrLeaves(root);
    fprintf(out,"number of leaves: %d\n", leaf_cnt);
    /// given root
    char c;
    fscanf(in,"%c", &c);
    fscanf(in,"%c", &c);
    interchange(root,c);
    fprintf(out,"interchanged node: %c", c);
    fputs("\nPRE: ",out);
    preorder(root, out);
    fputs("\nIN: ",out);
    inorder(root, out);
    fputs("\nPOST: ",out);
    postorder(root, out);
    return 0;
}
