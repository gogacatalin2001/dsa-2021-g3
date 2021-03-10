#include <stdio.h>
#include <stdlib.h>
/// node type
typedef struct node
{
    int data;
    struct node *next;
} NodeT;
/// header cell
typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;
/// create empty SLL
ListT *createEmptySLL()
{
    ListT *listPtr = (ListT *)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}
/// create and fill a node
NodeT *createAndFillNode(unsigned int data)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->data = data;
        p->next = NULL;
    }
    return p;
}
/// check if the list is non-empty
int isEmpty (ListT *listPtr)
{
    if (listPtr->count == 0) return 1;
    return 0;
}
/// inserting a node at the end
void insertAtRear (ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if (isEmpty(listPtr))
            listPtr->first = p;
        else listPtr->last->next = p;
        listPtr->last = p;
        listPtr->count++;
    }
}
/// find the intersection of to SLL
NodeT *findIntersection (ListT *A, ListT *B)
{
    NodeT *p = NULL, *q = NULL; /// p - pointer for the shorter list, q - poniter for the longer
    int diff = A->count - B->count, n; ///diff gives us, how many elements are not needed to be compared
    if (diff < 0)
        {p = A->first; q = B->first; n = B->count;}
    else {p = B->first; q = A->first; n = A->count;}
    diff = abs(diff);
    for (int i = 1; i <= diff; i++)
    {
        q = q->next; ///here we advance in the longer list, without having to compare these element
    }
    for (int i = diff; i <= n; i++)
    {
        if (p == q) return p; ///if the addresses are the same, we found the intersection
        p = p->next;
        q = q->next;
    }
    return NULL;
}
/// display the list
void display (ListT *listPtr)
{
        NodeT *p = listPtr->first;
        while (p != NULL)
        {
            printf("%d ", p->data);
            p = p -> next;
        }
        putchar('\n');
}
int main()
{
    ListT *A = NULL, *B = NULL, *C = NULL;
    A = createEmptySLL();
    B = createEmptySLL();
    C = createEmptySLL();

    NodeT *comm1, *comm2, *comm3;
    comm1 = createAndFillNode(7);
    comm2 = createAndFillNode(21);
    comm3 = createAndFillNode(45);

    insertAtRear(A,createAndFillNode(12));
    insertAtRear(A,createAndFillNode(5));
    insertAtRear(A,comm1);
    insertAtRear(A,comm2);
    insertAtRear(A,comm3);
    display(A);

    insertAtRear(B,createAndFillNode(31));
    insertAtRear(B,createAndFillNode(15));
    insertAtRear(B,createAndFillNode(9));
    insertAtRear(B,createAndFillNode(4));
    insertAtRear(B,comm1);
    insertAtRear(B,comm2);
    insertAtRear(B,comm3);
    display(B);

    NodeT *inter = findIntersection(A,B);
    if (inter)
    printf("intersection value: %d\n", inter->data);
    else puts("do not intersect\n");

    display(B);

    insertAtRear(C,createAndFillNode(11));
    insertAtRear(C,createAndFillNode(2));
    insertAtRear(C,createAndFillNode(33));
    insertAtRear(C,createAndFillNode(52));
    display(C);

    inter = findIntersection(B,C);
    if (inter)
    printf("intersection value: %d\n", inter->data);
    else puts("do not intersect\n");
    return 0;
}
