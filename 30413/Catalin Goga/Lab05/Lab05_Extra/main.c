#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tree node structure
typedef struct node_type
{
    char charStr[10];
    struct node_type *left, *right;
} NodeT;

/*/ list node structure
typedef struct list_node
{
    NodeT *node;
    struct list_node *next;
}ListNodeT;

// list structure
typedef struct
{
    int count;
    ListNodeT *first;
}ListT;

// create the list
ListT *createEmptyList()
{
    ListT *listPtr = (ListT*)calloc(1,sizeof(ListT));/// allocate memory fot the list
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = NULL;
    }
    return listPtr;
}

// create list node
ListNodeT *createSLLNode(NodeT *node)
{
    ListNodeT *p = (ListNodeT*)calloc(1,sizeof(ListNodeT));/// allocate memory for the node
    if(p)
    {
        p->node = node;
        p->next = NULL;
    }
    return p;
}
// purge list
void purge(ListT *listPtr)
{
    ListNodeT *p;
    while(listPtr->first != NULL)
    {
        p = listPtr->first;
        listPtr->first = p->next;
        free(p);
    }
    listPtr->count = 0;
    free(listPtr);
}

// stack functions
int push(ListT *listPtr, ListNodeT *p)
{
    if(listPtr)
    {
        // list is nonempty
        if(listPtr->count != 0)
        {
            p->next = listPtr->first;// list is empty
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;// success
    }
    return 0;// failure
}

int pop(ListT *listPtr)
{
    ListNodeT *p;
    if(listPtr->first != NULL)
    {

        // for non-empty list
        p = listPtr->first;
        listPtr->first = p->next;
        free(p);// free memory
        listPtr->count--;
        return 1;// success
    }
    return 0;// failure
}

ListNodeT *top(ListT *listPtr)
{
    return listPtr->first;
}

void printList(ListT *listPtr)
{
    ListNodeT *p = listPtr->first;
    while(p)
    {
        printf("%s ", p->node->charStr);
        p = p->next;
    }
    printf("\n");
}
 */
// display error message
void error(const char *msg)
{
    printf(msg);
    exit(1);
}

// tree functions
// create tree node
NodeT *createTreeNode(char *charStr)
{
    NodeT *temp = (NodeT*)calloc(1,sizeof(NodeT));
    // if the node is created add the string to the node
    // left and right pointers are initialized to NULL
    if(temp)
    {
        strcpy(temp->charStr, charStr);
        temp->left = temp->right = NULL;
    }
    else
        error("Not enough space for creating the node!\n");
    return temp;
}

void deleteTree(NodeT *root)
{
    if(root != NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

void preorder(FILE *out, NodeT *root, int level)
{
    int i;
    if(root != NULL)
    {
        for(i = 0; i<= level; i++)  fprintf(out, "  ");
        fprintf(out, "%s\n", root->charStr);
        preorder(out, root->left, level + 1);
        preorder(out, root->right, level + 1);
    }

}

void inorder(FILE *out, NodeT *root, int level)
{
    int i;
    if(root != NULL)
    {
        inorder(out, root->left, level + 1);
        for(i = 0; i<= level; i++)  fprintf(out, "  ");
        fprintf(out, "%s\n", root->charStr);
        inorder(out, root->right, level + 1);
    }
}

void postorder(FILE *out, NodeT *root, int level)
{
    int i;
    if(root != NULL)
    {
        postorder(out, root->left, level + 1);
        postorder(out, root->right, level + 1);
        for(i = 0; i<= level; i++)  fprintf(out, "  ");
        fprintf(out, "%s\n", root->charStr);
    }
}

NodeT *createBinTree(FILE *in)
{
    NodeT *p = NULL;
    char charStr[10];
    // read the string
    fscanf(in, "%s", charStr);
    p = createTreeNode(charStr);
    // if the string is an operand return the operand
    if(( (charStr[0] != '*') && (charStr[0] != '/') && (charStr[0] != '+') && (charStr[0] != '-') ) || (charStr[1] != '\0'))
    {
        return p;
    }
    // if the string is an operator add it to the tree
    else if( ((charStr[0] == '*') || (charStr[0] == '/') || (charStr[0] == '+') || (charStr[0] == '-')) && (charStr[1] == '\0'))
    {
        p->left = createBinTree(in);
        p->right = createBinTree(in);
    }
    return p;
}


int main(int argc, char **argv)
{
    FILE *in, *out;

    // check for correct opening of the files
    if((in = fopen(argv[1], "r")) == NULL)
        error("Can't open the input file!");
    if((out = fopen(argv[2], "w")) == NULL)
        error("Can't open the output file!");

    // create the tree
    NodeT *root = NULL;
    root = createBinTree(in);

    // print the tree in order
    fprintf(out, "Inorder traversal:\n\n");
    inorder(out, root, 0);

    // free the memory
    deleteTree(root);

    // close the files
    fclose(in);
    fclose(out);

    return 0;
}
