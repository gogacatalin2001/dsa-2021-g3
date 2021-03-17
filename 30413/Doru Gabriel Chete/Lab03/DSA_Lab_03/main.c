#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int count;
    char s[15];
    struct node *next;
    struct node *prev;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} DLListT;

DLListT *createEmptyDLL()
{
    DLListT *listPtr = (DLListT*)malloc(sizeof(DLListT));
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = NULL;
        listPtr->last = NULL;
    }
    return listPtr;
}

int isEmpty(DLListT* listPtr)
{
    if(listPtr->first == NULL || listPtr->last == NULL)
    {
        return 1;
    }
    return 0;
}

NodeT *createDLLNode(char word[15])
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->count = 1;
        strcpy(p->s, word);
        p->next = p->prev = NULL;
    }
    return p;
}

int insertAtRear(DLListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if(isEmpty(listPtr))
        {
            listPtr->first = listPtr->last = p;
            p->prev = p->next = NULL ;
        }
        else
        {
            listPtr->last->next = p;
            p->prev = listPtr->last;
            p->next = NULL;
            listPtr->last = p;
        }
        listPtr->count++;
        return 1;
    }
    return 0;
}

void swap(NodeT *p, NodeT *q)
{
    char tempString[15];
    int tempCount;
    strcpy(tempString, p->s);
    tempCount = p->count;
    strcpy(p->s, q->s);
    p->count = q->count;
    strcpy(q->s, tempString);
    q->count = tempCount;
}

void bubbleSort(DLListT *listPtr)
{
    NodeT *p;
    NodeT *lastp = NULL;
    int swapped;
    do
    {
        swapped = 0;
        p = listPtr->first;
        while(p->next != lastp)
        {
            if(strcmp(p->s,p->next->s) > 0)
            {
                swap(p, p->next);
                swapped = 1;
            }
            p = p->next;
        }
        lastp = p;

    }while(swapped);





}

int main(char argc, char *argv[])
{
    char current[15];
    int ok;
    FILE *fo;
    FILE *fo2;
    fo = fopen(argv[1], "r");
    fo2 = fopen(argv[2], "w");
    DLListT *wordList;
    wordList = createEmptyDLL();
    while(fscanf(fo, "%s", current) != EOF)
    {
        ok = 1;
        NodeT *p;
        for(p = wordList->first; p != NULL; p = p->next)
        {
            if(strcmp(p->s, current) == 0)
            {
                p->count++;
                ok = 0;
            }
        }
        if(ok)
        {
            NodeT *w;
            w = createDLLNode(current);
            insertAtRear(wordList, w);
        }
    }
    //now sort
    bubbleSort(wordList);
    //
    NodeT *p;
    fprintf(fo2, "Ascending order:\n");
    for(p = wordList->first; p != NULL; p = p->next)
    {
        fprintf(fo2, "%s:%d\n", p->s, p -> count);
    }

    fprintf(fo2, "Descending order:\n");
    for(p = wordList->last; p != NULL; p = p->prev)
    {
        fprintf(fo2, "%s:%d\n", p->s, p -> count);
    }
    return 0;
}
