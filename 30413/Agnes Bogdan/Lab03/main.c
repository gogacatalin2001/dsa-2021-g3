#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_type
{
    char key[10];
    struct node_type *next;
    struct node_type *prev;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} DLListT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

/* Create an empty list */
ListT *createEmptyDLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
    listPtr->count = 0;
    listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createDLLNode(char givenKey[])
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
    strcpy(p->key, givenKey);
    p->next = p->prev = NULL;

    }
return p;
}

int isEmpty(ListT *listPtr)
{
    if(listPtr -> first == NULL && listPtr -> last == NULL && listPtr -> count == 0)
        return 1;
    else return 0;
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    { // the list is non null
    if (isEmpty(listPtr))
    {
    // p will be the sole node in the list
    listPtr->first = listPtr->last = p;
    p->prev = p->next = NULL; // p is the first and single node
    }
    else
    { // non-empty list
    listPtr->last->next = p; // chain after the former last node
    p->prev = listPtr->last; // p is after the former last node
    p->next = NULL; // p is the last node
    }
    listPtr->count++; // increment number of nodes
    return 1; // success
    }
    return 0; // failure
}

int printDLL(DLListT *listPtr)
{
    NodeT *current = listPtr->first;
    if(isEmpty(listPtr)) printf("empty list");
    while(current != 0)
    {
        printf("%s ", current->key);
        current = current ->next;
    }
    printf("\n");
}

int searchForNode(DLListT *listPtr,  char givenKey[])
{
    int ok = 0;
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
    {
    if ( strcmp(p->key, givenKey ) == 0)
    {ok = 1;
    break;}
        p = p->next;

    }
    if(ok == 1) return 1;
    else return 0;
}
int searchCount(DLListT *listPtr,  char givenKey[])
{
    int ok = 0;
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
    {
    if ( strcmp(p->key, givenKey ) == 0)
    {ok++;
    break;}
        p = p->next;

    }
    return ok;
}
int main()
{
    FILE *f = fopen("in.txt", "r");
    FILE *g = fopen("out.txt", "w");
    char *text = (char*)malloc(sizeof(char));
    char *c;
    int i = 0;
    NodeT *n;
    ListT *list;
    list = createEmptyDLL();

    while( (c = fgetc(f)) != EOF)
    {
        text[i++] = c;
        char *text = (char*)realloc(text, (i + 1) * sizeof(char));
    }
    text[i++] = ' ';
    text[i] = '\0';
    //printf("%s\n", text);

    char *word = (char*)malloc(sizeof(char));
    int j = 0;
    i = 0;
    //printf("%c", text[0]);
    while(text[i] != '\0')
    {
        //printf("%c", text[i]);
        if(text[i] != ' ') {word[j++] = text[i];
        }
        else {
            word[j] = '\0';
            //printf("%s ", word);
            n = createDLLNode(word);
            insertAtRear(list, n);

            j = 0;
        }
        i++;
    }


    int nr;
    NodeT *p;
    NodeT *P;
    for ( p = list->first; p != NULL; p = p->next)
    {
        i = 0;
        for ( P = list->first; P != NULL; P = P->next)
        if(strcmp(p->key, P->key) == 0) i++;
        printf("%s: %d\n", p->key, i);
    }
    //printDLL(list);






    free(word);
    fclose(g);
    fclose(f);
    free(text);
    return 0;
}
