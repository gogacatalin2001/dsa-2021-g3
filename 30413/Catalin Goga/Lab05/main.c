#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    char letter;
    struct node_type *left, *right;
} NodeT;

void error(const char *msg)
{
    printf(msg);
    exit(1);
}

NodeT *createNode(char letter)
{
    NodeT *temp = (NodeT*)calloc(1,sizeof(NodeT));
    // if the node is created add the letter and the
    // left and right pointers are initialized to NULL
    if(temp)
    {
        temp->letter = letter;
        temp->left = temp->right = NULL;
    }
    else
        error("Not enough space for creating the node!\n");
    return temp;
}


NodeT *insertNode(NodeT *root, char letter)
{
    // if the root is NULL the tree is empty
    if(root == NULL)
    {
        root = createNode(letter);
        return root;
    }
    else
    {
        if(letter < root->letter)// if the given letter is smaller than the current node's letter, go left
            root->left = insertNode(root->left, letter);
        else if (letter > root->letter)// if the given letter is bigger than the current node's letter, go right
            root->right = insertNode(root->right, letter);
        else
            printf("\nThe node with letter %c is already in the tree!\n", letter);
    }
    return root;
}

NodeT *findNode(NodeT *root, char letter)
{
    if(root == NULL)
        return NULL; // empty tree
    for(NodeT *q = root; q != NULL;)
    {
        if(q->letter == letter)// node was found
            return q;
        else if(letter < q->letter)// if the given letter is smaller than the current node's key, go left
            q = q->left;
        else q = q->right;// if the given letter is bigger than the current node's key, go right
    }
    return NULL;// node was not found
}

NodeT *findMin(NodeT *p)
{
    if(p == NULL)
        return NULL;// tree is empty
    if(p->left)
        return findMin(p->left);// go to the left subtree
    else
        return p;
}

NodeT *findMax(NodeT *p)
{
    if(p == NULL)
        return NULL;// tree is empty
    if(p->right)
        return findMax(p->right);// go to the right subtree
    else
        return p;
}

NodeT *deleteNode(NodeT *root, char letter)
{
    if(root == NULL)
        printf("\nElement not foun!\n");

    if(letter < root->letter)// searched node is in the left subtree
        root->left = deleteNode(root->left, letter);

    else if(letter > root->letter)// searched node is in the right subtree
        root->right = deleteNode(root->right, letter);
    else
    {
        if(root->left && root->right)
        {
            // find the min node in the right subtree
            NodeT *temp = findMin(root->right);
            // replace the current node with the minimum root
            root->letter = temp->letter;
            // delete the minimum node which is now duplicated
            root->right = deleteNode(root->right, temp->letter);
        }
        else
        {
            NodeT *temp = root;
            if(root->left == NULL)
                root = root->right;
            else if(root->right == NULL)
                root = root->left;
            free(temp);// delete
        }
    }
    return root;
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
        fprintf(out, "%c\n", root->letter);
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
        fprintf(out, "%c\n", root->letter);
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
        fprintf(out, "%c\n", root->letter);
    }
}

void processInput(FILE *in, FILE *out, NodeT *root)
{
    char command[3];

    while(fscanf(in, "%s", command) != EOF)
    {
        NodeT *temp;
        switch(command[0])
        {
        case 'i':
            if(root == NULL)
                root = createNode(command[1]);
            else
                insertNode(root, command[1]);
            break;
        case 'd':
            deleteNode(root, command[1]);
            fprintf(out, "\nNode %c was deleted.\n", command[1]);
            break;
        case 'f':
            temp = findNode(root, command[1]);
            if(temp)
                fprintf(out, "The searched node is: %c\n", temp->letter);
            break;
        case 't':
            if(command[1] == 'p')
            {
                fprintf(out, "\nPreorder:\n");
                preorder(out, root, 0);
                fprintf(out, "\n");
            }
            else if (command[1] == 'P')
            {
                fprintf(out, "\nPostorder:\n");
                postorder(out, root, 0);
                fprintf(out, "\n");
            }
            else if (command[1] == 'i')
            {
                fprintf(out, "\nInorder:\n");
                inorder(out, root, 0);
                fprintf(out, "\n");
            }
            break;
        case 'g':
            if(command[1] == 'm')
            {
                temp = findMin(root);
                if(temp)
                    fprintf(out, "Min node is: %c\n", temp->letter);
            }
            else if (command[1] == 'M')
            {
                temp = findMax(root);
                if(temp)
                    fprintf(out, "Max node is: %c\n", temp->letter);
            }
            break;
        };
    }
    printf("Done processing input file!");
}

int main(int argc, char **argv)
{
    FILE *in,*out;
    // check for correct file opening
    if((in = fopen(argv[1],"r")) == NULL)
        error("\nCouldn't open the input file!");
    if((out = fopen(argv[2],"w")) == NULL)
        error("\nCouldn't open the output file!");


    NodeT *root = NULL;
    processInput(in, out, root);

    // close the files
    fclose(in);
    fclose(out);

    // free the memoy
    deleteTree(root);

    return 0;
}
