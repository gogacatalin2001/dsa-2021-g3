#include <stdio.h>
#include <stdlib.h>

// first, here are some functions taken from the laboratory guide
typedef struct node
{
    int key;
    struct node *next;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

ListT *createEmptySSL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->key = key;
        p->next = NULL;
    }
    return p;
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        if (listPtr->count == 0)
            listPtr->first = p;
        else listPtr->last->next = p;
        listPtr->last = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

NodeT *find(ListT *listPtr, int givenKey)
{
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
        if ( p->key == givenKey )
            return p;
        else p = p->next;
    return NULL;
}

int deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr->first;
    while ( q != NULL )
    {
        if ( q->key == givenKey ) break;
        q1 = q;
        q = q->next;
    }
    if ( q != NULL )
    {
        if ( q == listPtr->first )
        {
            listPtr->first = listPtr->first->next;
            free( q );
            if ( listPtr->first == NULL )
                listPtr->last = NULL;
        }
        else
        {
            q1->next = q->next;
            if ( q == listPtr->last )
                listPtr->last = q1;
            free( q );
        }
        listPtr->count--;
        return 1;
    }
    return 0;
}

// function that takes the number from the input lines (used only if on the line are numbers)
int getCommandNumber(char s[])
{
    int i = 2, nr = 0;
    while (s[i]!=')')
    {
        nr = nr * 10 + (int)(s[i] - '0');
        i++;
    }
    return nr;
}

// function used to print the elements of the list
void printList(ListT *listPtr, FILE *out)
{
    int i=0;
    NodeT *truck = listPtr->first;
    while (i<listPtr->count)
    {
        fprintf(out, " %d", truck->key);
        truck = truck->next;
        i++;
    }
    fprintf(out, "\n");
}

int main(int argc, char *argv[])
{
    ListT *road = createEmptySSL(), *garage = createEmptySSL();
    int key;

    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Input file not found or not introduced!");
        exit(0);
    }
    FILE *out = fopen(argv[2], "w");
    if (out == NULL)
    {
        printf("Output file not introduced!");
        exit(0);
    }
    // we don't check if the output file exists because if it doesn't, it's created automatically

    char command[10]; // each line is saved in a string that will be reused
    while (fscanf(in, "%s", command) != EOF)
    {
        switch(command[0])
        {
            case 'R':
                key = getCommandNumber(command); // we get the number from the line
                insertAtRear(road, createSLLNode(key));
                break;
            case 'E':
                key = getCommandNumber(command);
                if (find(road, key) != NULL)
                {
                    if (road->first->key == key)
                    {
                        insertAtRear(garage, createSLLNode(key));
                        deleteByKey(road, key);
                    }
                    else fprintf(out, "error: %d not at road's exit!\n", key);
                }
                else fprintf(out, "error: %d not on road!\n", key);
                break;
            case 'X':
                key = getCommandNumber(command);
                if (find(garage, key) != NULL)
                {
                    if (garage->last->key == key)
                    {
                        insertAtRear(road, createSLLNode(key));
                        deleteByKey(garage, key);
                    }
                    else fprintf(out, "error: %d not at garage's exit!\n", key);
                }
                else fprintf(out, "error: %d not in garage!\n", key);

                break;
            case 'S':
                if (command[2]== 'G') // we print the garage list
                {
                    fprintf(out, "G:");
                    if (garage->count != 0)
                        printList(garage, out);
                    else fprintf(out, " none\n");
                }
                else // we print the road list
                {
                    fprintf(out, "R:");
                    if (road->count != 0)
                        printList(road, out);
                    else fprintf(out, " none\n");
                }
                break;
        }
    }
    fclose(in);
    fclose(out);
    printf("Success\n");
    return 0;
}
