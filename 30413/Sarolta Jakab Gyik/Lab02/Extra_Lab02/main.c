#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

ListT *createEmptySLL()
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
int isEmpty( ListT *listPtr)
{
    if((listPtr->first == NULL) && (listPtr->last == NULL))
        return 1;
    return 0;
}
int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        p->next = listPtr->first;
        if (isEmpty(listPtr))
        {
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        if (isEmpty(listPtr))
        {
            listPtr->first = p;
        }
        else
        {
            listPtr->last->next = p;
        }
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
        {
            return p;
        }
        else
            p = p->next;
    return NULL;
}

NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if ( listPtr->first != NULL )
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        listPtr->count--;
        if ( listPtr->first == NULL )
            listPtr->last = NULL;
        return p;
    }
    return NULL;
}

NodeT *deleteLast(ListT *listPtr)
{
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr->first;
    if ( q != NULL )
    {
        while ( q != listPtr->last )
        {
            q1 = q;
            q = q->next;
        }
        if ( q == listPtr->first )
        {
            listPtr->first = listPtr->last = NULL;
        }
        else
        {
            q1->next = NULL;
            listPtr->last = q1;
        }
    }
    return q;
}

int deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr -> first;
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
            if ( listPtr->first == NULL ) listPtr->last = NULL;
        }
        else
        {
            q1->next = q->next;
            if ( q == listPtr->last ) listPtr->last = q1;
            free( q );
        }
        return 1;
    }
    return 0;
}
void outputList(FILE *g, ListT *myList)
{
    if((myList->count == 0) && (!myList ->first) && (!myList -> last))
        fprintf(g, "Empty list\n");
    else
    {
        NodeT *r = myList->first;
        while(r != NULL)
        {
            fprintf(g, "%d ", r->key);
            r = r -> next;
        }
    }
    fprintf(g, "\n");
}
void backtrackOut(FILE *g, ListT *myList, int nrNodes, NodeT *r)
{
    if((myList->count == 0) && (!myList ->first) && (!myList -> last))
        fprintf(g, "Empty list\n");
    if(!nrNodes || r == NULL)
        return 0;
    fprintf(g, "%d ", r->key);
    nrNodes--;
    r = r->next;
    backtrackOut(g, myList, nrNodes, r);
}
NodeT *search(ListT *myList, int nrNodes)
{
    NodeT *r = myList->first;
    for(int i = 0; i < nrNodes; i++)
        r = r->next;
    return r;
}
void purge(ListT *listPtr)
{
    NodeT *p;
    while ( listPtr->first != NULL )
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free( p );
    }
    listPtr->last = NULL;
    listPtr->count = 0;
}
int main()
{
    FILE *f = fopen("input.dat", "r");
    FILE *g = fopen("output.dat", "w");
    char line[20];
    ListT *myList;
    myList = createEmptySLL();
    while(fgets(line, sizeof(line), f))
    {
        int j = 3, nrNode = 0, x = 0, nrElements = 0;
        char nr[5] = "";
        while(j != strlen(line))
        {
            if(line[j] >= '0' && line[j] <= '9' && x == 0)
            {
                nr[nrElements++] = line[j];
                x = j;
            }
            else if(line[j] >= '0' && line[j] <= '9')
                nr[nrElements++] = line[j];
            j++;
        }
        if(x != 0)
        {
            nrNode = atoi(nr);
            printf("The node is:%d\n", nrNode);
            line[x-1] = '\0';
        }
        //printf("The length is %d\n", strlen(line));
        printf("The string is %ses ennyi\n", line);
        char *newLine;
        if(line[0] == 'A' && line[1] == 'F')
        {
            NodeT *p;
            p = createSLLNode(nrNode);
            if(!p)
                printf("Node not created");
            int x = insertAtFront(myList, p);
            if(!x)
                printf("Node not inserted at front");
        }
        else
        {
            if(line[0] == 'A' && line[1] == 'L')
            {
                NodeT *p;
                p = createSLLNode(nrNode);
                insertAtRear(myList, p);
            }
            else
            {
                if(line[0] == 'D' && line[1] == 'L')
                {
                    deleteLast(myList);
                }
                else
                {
                    if(line[0] == 'D' && line[1] == 'F')
                    {
                        deleteFirst(myList);
                    }
                    else
                    {
                        if(line[0] == 'D' && line[1] == 'O' && line[2] == 'O' && line[3] == 'M')
                        {
                            purge(myList);
                        }
                        else
                        {
                            if(line[0] == 'D' && line[1] == 'E')
                            {
                                NodeT *p;
                                p = find(myList, nrNode);
                                if(p != NULL)
                                    deleteByKey(myList, nrNode);
                            }
                            else
                            {
                                if(line[0] == 'P' && line[1] == 'R' && !nrNode)
                                {
                                    outputList(g, myList);
                                }
                                else if(line[0] == 'P' && line[1] == 'R' && nrNode != 0 && line[6] == 'F')
                                {
                                    NodeT *p;
                                    p = myList->first;
                                    if(p == NULL)
                                        fprintf(g, "Empty list");
                                    for(int i = 0; i < nrNode && p != NULL; i++)
                                    {
                                        fprintf(g, "%d ", p->key);
                                        p = p->next;
                                    }
                                    fprintf(g, "\n");
                                }
                                else if(line[0] == 'P' && line[1] == 'R' && nrNode != 0 && line[6] == 'L')
                                {
                                    NodeT *r;
                                    r = search(myList, myList->count - nrNode);
                                    backtrackOut(g, myList, nrNode, r);
                                }
                            }
                        }
                    }
                }
            }
        }
        //outputList(g, myList);
        //printf("\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
