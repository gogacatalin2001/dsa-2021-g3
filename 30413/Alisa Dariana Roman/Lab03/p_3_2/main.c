#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char key[50];
    int keyCount;
    struct node *next;
    struct node *prev;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

ListT *createDLList()
{
    ListT *listPtr = (ListT*) malloc(sizeof(ListT));
    if(listPtr) {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createDLLNode(char s[])
{
    NodeT *p = (NodeT *) malloc(sizeof(NodeT));
    if (p) {
        strcpy(p->key, s);
        p->next = p->prev = NULL;
        p->keyCount = 1;
    }
    return p;
}

NodeT *find(ListT *listPtr, char s[])
{
    NodeT *p;
    p = listPtr->first;
    while (p != NULL) {
        if (!strcmp(p->key, s)) {
            return p;
        }
        else
            p = p->next;
    }
    return NULL;
}

int isEmpty(ListT *listPtr)
{
    if(listPtr->count == 0 && listPtr->first == NULL && listPtr->last == NULL)
        return 1;
    return 0;
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if(listPtr) {
        if(isEmpty(listPtr)) {
            listPtr->last = p;
        }
        else {
            p->next = listPtr->first;
            listPtr->first->prev = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if(listPtr) {
        if(isEmpty(listPtr)) {
            listPtr->first = p;
        }
        else {
            listPtr->last->next = p;
            p->prev = listPtr->last;
        }
        listPtr->last = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

void insertNode(ListT *listPtr, char s[])
{
    NodeT *p = createDLLNode(s);
    NodeT *q = NULL;
    if(isEmpty(listPtr)) {
        listPtr->first = listPtr->last = p;
    }
    else {
        if(stricmp(s, listPtr->first->key) < 0) {
            if( !insertAtFront(listPtr, p) )
                printf("error");
        }
        if(stricmp(s, listPtr->last->key) > 0) {
            if( !insertAtRear(listPtr, p) )
                printf("error");
        }
        else {
            q = listPtr->first->next; /// set q the second node from list
            while(stricmp(s, q->key) > 0) {
                q = q -> next;
            }
            q->prev->next = p;
            p->prev = q->prev;
            p->next = q;
            q->prev = p;
        }
    }
    listPtr->count++;
}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    /** Algorithm
    -create empty doubly linked list
    -while reading the words from text file named argv[1] :
        -check if the word is contained already in the d. l. list
            -if yes increase keyCount with 1
            -else use function insertNode : this function creates a node with
            key = s, keyCount = 1, compares s with first node key, last node key and with the node
            inbetween and places s corespondingly: at every step the list is sorted in ascending order
    **/
    ListT *list = createDLList();
    char s[100];
    NodeT *aux = NULL;
    NodeT *p = NULL;


    while(fscanf(fileI, "%s", s) != EOF) {
        aux = find(list, s);
        if (aux != NULL) {
            aux->keyCount++;
        }
        else {
            insertNode(list, s);    /// this function creates and inserts a node with key = s, keyCount = 1
                                    /// sorted in ascending order
        }
    }

    ///displaying the list:
    for(p = list->first; p != NULL; p = p->next) {
        fprintf(fileO, "%s:%d\n", p->key, p->keyCount);
    }

    return 0;
}
