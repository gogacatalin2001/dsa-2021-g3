///experimenting with code from the lab material
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    ListT *listPtr = (ListT*) malloc(sizeof(ListT));
    if(listPtr) {
        listPtr -> count = 0;
        listPtr -> first = listPtr -> last = NULL;
    }
    return listPtr;
}

NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT *) malloc(sizeof(NodeT));
    if (p) {
        p -> key = key;
        p -> next = NULL;
    }
    return p;
}

bool isEmpty(ListT *listPtr)
{
    if(listPtr -> count == 0 && listPtr -> first == NULL && listPtr -> last == NULL)
        return 1;
    return 0;
}

int insertAtFront(ListT *listPtr, NodeT *p) ///insert node p at the front of list <- listPtr
{
    if(listPtr) {
        p -> next = listPtr -> first;
        if(isEmpty(listPtr)) {
            listPtr -> last = p; /// p will be the sole node in the list
        }
        listPtr -> first = p;
        listPtr -> count++;
        return 1;
    }
    return 0;
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if(listPtr) {
        if(isEmpty(listPtr)) {
            listPtr -> first = p; /// p will be the sole node in the list
        }
        else {
            listPtr -> last -> next = p;
        }
        listPtr -> last = p;
        listPtr -> count ++;
        return 1;
    }
    return 0;
}



int main()
{
    ListT *listPtr;
    listPtr = createEmptySLL();

    listPtr -> first = listPtr -> last = createSLLNode(1);

    listPtr -> count ++;

    if(isEmpty(listPtr))
        printf("da");

    NodeT *x = createSLLNode(2);
    insertAtRear(listPtr, x);


    /// insert node p before a node given by its key
    /// 1. search for the node containing a given key
    int givenKey = 2;
    NodeT *p = createSLLNode(10);
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr -> first;
    while(q != NULL) { /// going through the list
        if (q -> key == givenKey) {
            break;
        }
        q1 = q;         /// q1 will be the node before q
        q = q -> next;
    }

    /// insert node p before node q
    if( q != NULL ) {
        if( q == listPtr -> first ) { /// p will be the first node of the list
            p -> next = listPtr -> first;
            listPtr -> first = p;
        }
        else {
            q1 -> next = p;
            p -> next = q;
        }
        listPtr -> count ++;
    }

    printf("%d\n", listPtr -> first -> next -> next -> key); /// 1 , 10, 2
    return 0;
}
