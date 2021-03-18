#include <stdio.h>
#include <stdlib.h>

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
    if(c == '*')
    {
        return NULL;
    }
    else
    {
        p = (NodeT*)malloc(sizeof(NodeT));
        if(p == NULL)
        {
            fatalError("Out of space in createBinTree");
        }
        p->id = c;
        p->left = createBinTree();
        p->right = createBinTree();
    }
    return p;
}

void fatalError(const char *msg)
{
    printf(msg);
    printf("\n");
    exit(1);
}

void preorder(NodeT *p, int level)
{
    if(p != NULL)
    {
        for(int i = 0; i <= level; i++)
        {
            printf(" ");
        }
        printf("%2.2c\n", p->id);
        preorder(p->left, level + 1);
        preorder(p->right, level + 1);
    }
}

void inorder (NodeT *p, int level)
{
    if( p != NULL)
    {
        inorder(p->left, level +1);
        for(int i = 0; i <= level; i++)
        {
            printf(" ");
        }
        printf("%2.2c\n", p->id);
        inorder(p->right, level + 1);
    }

}

void postorder(NodeT *p, int level)
{
    if(p != NULL)
    {
        postorder(p->left, level+1);
        postorder(p->right, level+1);
        for(int i = 0; i <= level; i++)
        {
            printf(" ");
        }
        printf("%2.2c\n", p->id);
    }

}

void interchangeSubtrees(NodeT *p)
{
    NodeT *aux;
    aux = p->left;
    p->left = p->right;
    p->right = aux;
}

int heightOfTree(NodeT *p)
{
    if(p == NULL)
    {
        return -1;
    }
    else
    {
        int leftHeight = heightOfTree(p->left);
        int rightHeight = heightOfTree(p->right);
        if(leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}

int numberOfLeaves(NodeT *p)
{
    if(p == NULL)
    {
        return 0;
    }
    if((p->left == NULL) && (p -> right == NULL))
    {
        return 1;
    }
    else
    {
        return numberOfLeaves(p->left) + numberOfLeaves(p->right);
    }
}

int main()
{
    NodeT *p;
    p = createBinTree();
    int mode;
    printf("Please enter working mode: 1 for interchanging left and right subtrees of a given node, 2 for the height of a binary tree, 3 for the number of leaves\n");
    scanf("%d", &mode);
    switch(mode)
    {
    case 1:
        interchangeSubtrees(p);
        printf("\nPreorder:\n");
        preorder(p, 0);
        printf("\nInorder:\n");
        inorder(p, 0);
        printf("\nPostorder:\n");
        postorder(p, 0);
        break;
    case 2:
        printf("Height is: %d", heightOfTree(p));
        break;
    case 3:
        printf("Number of leaves is: %d", numberOfLeaves(p));
        break;
    }
    return 0;
}
