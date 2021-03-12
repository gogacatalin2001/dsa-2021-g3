#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    int id;
    struct node_type *left, *right;
}NodeT;

void fatalError(const char *msg)
{
    printf(msg);
    exit(1);
}

//binary tree
NodeT *createBinTree(FILE *in)
{
    NodeT *p;
    int id;
    //read the id of the node
    fscanf(in,"%d",&id);
    if(id == 0)
        return NULL;
    // alocate memory for the node
    p = (NodeT*)calloc(1,sizeof(NodeT));
    if(p == NULL)
        fatalError("No memory for creating the tree!");
    // read the data
    p->id = id;
    p->left = createBinTree(in);
    p->right = createBinTree(in);
    return p;
}

// tree traversals
void preorder(FILE *out, NodeT *p, int level)
{
    if(p != NULL)
    {
        for(int i=0; i<level; i++)
            fprintf(out,"   ");
        fprintf(out,"%2.2d\n",p->id);
        preorder(out,p->left,level + 1);
        preorder(out,p->right,level + 1);
    }
}

void inorder(FILE *out, NodeT *p, int level)
{
    if(p != NULL)
    {
        inorder(out,p->left,level + 1);
        for(int i=0; i<level; i++)
            fprintf(out,"   ");
        fprintf(out,"%2.2d\n",p->id);
        inorder(out,p->right,level + 1);
    }
}

void postorder(FILE *out, NodeT *p, int level)
{
    if(p != NULL)
    {
        postorder(out,p->left,level + 1);
        postorder(out,p->right,level + 1);
        for(int i=0; i<level; i++)
            fprintf(out,"   ");
        fprintf(out,"%2.2d\n",p->id);
    }
}

void deleteTree(NodeT *p)
{
    if((p->left != NULL) && (p->right != NULL))
    {
        deleteTree(p->left);
        deleteTree(p->right);
    }
    else
        free(p);
    return;
}

//problem functions
void interchangeSubtrees(NodeT *p)
{
    NodeT *temp;
    temp = p->left;
    p->left = p->right;
    p->right = temp;
}

int maximum(int a, int b)
{
    if(a >= b)
        return a;
    return b;
}

int treeHeight(NodeT *p)
{
    if(p == NULL)
        return 0;
    else
        return maximum(treeHeight(p->left),treeHeight(p->right)) + 1;
}

int nbOfLeaves(NodeT *p)
{
    if(p != NULL)
    {
        if((p->left == NULL) &&
            (p->right == NULL))
            return 1;
        else
            return nbOfLeaves(p->left) + nbOfLeaves(p->right);
    }
    return 0;
}


int main(int argc, char **argv)
{
    // open the input and output files
    FILE *in,*out;
    if((in = fopen(argv[1],"r")) == NULL)
        fatalError("Could not open input file!");
    if((out = fopen(argv[2],"w")) == NULL)
        fatalError("Could not open output file!");

    //create the binary tree
    NodeT *tree;
    tree = createBinTree(in);
    //print the tree
    fprintf(out,"Preorder:\n");
    preorder(out,tree,0);
    fprintf(out,"\nInorder:\n");
    inorder(out,tree,0);
    fprintf(out,"\nPostorder:\n");
    postorder(out,tree,0);
    fprintf(out,"\n");

    //problem
    fprintf(out,"--------------------------\n");
    interchangeSubtrees(tree);
    fprintf(out,"After subtrees interchange:\n\n");
    fprintf(out,"Preorder:\n");
    preorder(out,tree,0);
    fprintf(out,"\nInorder:\n");
    inorder(out,tree,0);
    fprintf(out,"\nPostorder:\n");
    postorder(out,tree,0);
    fprintf(out,"\n");

    fprintf(out,"Number of leaves: %d\n",nbOfLeaves(tree));
    fprintf(out,"Height of the tree: %d\n",treeHeight(tree));
    //free the memory
    deleteTree(tree);

    //close the files
    fclose(in);
    fclose(out);

    return 0;
}
