#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key; /* an optional field identifying the data */
    /* other useful data fields */
    struct node *next; /* link to next node */
} NodeT;

typedef struct
{
    int count; /* an optional field */
    NodeT *first; /* link to the first node in the list */
    NodeT *last; /* link to the last node in the list */
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
        // what is done here depends on the data stored at the node
        p->key = key; // assignment allowed as the key is of a primitive type
        p->next = NULL;
    }
    return p;
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        p->next = listPtr->first;
        if (listPtr->count == 0)
        {
            // p will be the sole node in the list
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        if (listPtr->count == 0)
        {
            // p will be the sole node in the list
            listPtr->first = p;
        }
        else
        {
            // non-empty list
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++; // increment number of nodes
        return 1; // success
    }
    return 0; // failure
}

NodeT *find(ListT *listPtr, int givenKey)
{
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
        if ( p->key == givenKey ) /* Note. This comparison does work for primitive types only
        */
        {
            return p; /* key found in cell p */
        }
        else p = p->next;
    return NULL; /* not found */
}

NodeT *deleteLast(ListT *listPtr)
{
    NodeT *q, *q1;
    q1 = NULL; /* initialize */
    q = listPtr->first;
    if ( q != NULL )
    {
        /* non-empty list */
        while ( q != listPtr->last )
        {
            /* advance towards end */
            q1 = q;
            q = q->next;
        }
        if ( q == listPtr->first )
        {
            /* only one node */
            listPtr->first = listPtr->last = NULL;
        }
        else
        {
            /* more than one node */
            q1->next = NULL;
            listPtr->last = q1;
        }
        free( q );
        listPtr->count--;
    }
    return q;
}

int deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *q, *q1;
    q1 = NULL; /* initialize */
    q = listPtr->first;
    /* search node */
    while ( q != NULL )
    {
        if ( q->key == givenKey ) break;
        q1 = q;
        q = q->next;
    }
    if ( q != NULL )
    {
        /* found a node with supplied key */
        if ( q == listPtr->first )
        {
            /* is the first node */
            listPtr->first = listPtr->first->next;
            free( q ); /* release memory */
            if ( listPtr->first == NULL )
                listPtr->last = NULL;
        }
        else
        {
            /* other than first node */
            q1->next = q->next;
            if ( q == listPtr->last )
                listPtr->last = q1;
            free( q ); /* release memory */
        }
        listPtr->count--;
        return 1; // success
    }
    return 0; // failure
}

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

int main()
{
    ListT *road = createEmptySSL(), *garage = createEmptySSL();
    NodeT *truck;
    int key;

    char in_file_name[50], out_file_name[50];
    printf("Type the name of the input file: ");
    scanf("%s", in_file_name);
    FILE *in = fopen(in_file_name, "r");
    if (in == NULL)
    {
        printf("Input file not found!");
        exit(0);
    }
    printf("Type the name of the output file: ");
    scanf("%s", out_file_name);
    FILE *out = fopen(out_file_name, "w");
    if (out == NULL)
    {
        printf("Output file not found!");
        exit(1);
    }

    char command[10];
    while (fscanf(in, "%s", command) != EOF)
    {
        switch(command[0])
        {
            case 'R':
                /*truck->key = getCommandNumber(command);
                printf("%d\n", truck->key);
                insertAtRear(road, truck);
                break;*/
                key = getCommandNumber(command);
                insertAtRear(road, createSLLNode(key));
                break;
            case 'E':
                /*truck->key = getCommandNumber(command);
                printf("%d\n", truck->key);
                if (find(road, truck->key) == NULL)
                    printf("%d not on road!", truck->key);
                else
                {
                    insertAtRear(garage, truck);
                    deleteByKey(road, truck->key);
                }
                break;*/
                key = getCommandNumber(command);
                if (find(road, key) != NULL)
                {
                    //printf("%d\n", find(road, key)->key);
                    insertAtRear(garage, createSLLNode(key));
                    deleteByKey(road, key);
                }
                else fprintf(out, "error: %d not on road!\n", key);
                break;
            case 'X':
                /*truck->key = getCommandNumber(command);
                printf("%d\n", truck->key);
                if (garage->last->key != truck->key)
                    printf("%d not at exit!", truck->key);
                else
                {
                    insertAtFront(road, truck);
                    deleteLast(garage);
                }
                break;*/
                key = getCommandNumber(command);
                if (garage->last->key == key)
                {
                    insertAtFront(road, createSLLNode(key));
                    deleteLast(garage);
                }
                else fprintf(out, "error: %d not at exit!\n", key);

                break;
            case 'S':
                if (command[2]== 'G')
                {
                    fprintf(out, "G:");
                    if (garage->count != 0)
                        printList(garage, out);
                    else fprintf(out, " none\n");
                }
                else
                {
                    fprintf(out, "R:");
                    if (road->count != 0)
                        printList(road, out);
                    else fprintf(out, " none\n");
                }
                break;
        }
        //printList(road);
        //printList(garage);
    }
    fclose(in);
    fclose(out);
    return 0;
}
