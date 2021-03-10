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
    NodeT *first;
    NodeT *last;
} ListT;
/// create empty SLL
ListT *createEmptySLL()
{
    ListT *listPtr = (ListT *)malloc(sizeof(ListT));
    if (listPtr)
    {
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
/// inserting a node at the end
void insertAtRear (ListT *listPtr, NodeT *p)
{
    listPtr->last->next = p;
    listPtr->last = p;

}
/// find and remove duplicates
void removeDuplicates (ListT *listPtr)
{
    NodeT *p1 = listPtr->first, *p2 = listPtr->first, *del = NULL;
    while (p1->next != NULL)
    {
        while (p2->next != NULL)
        {
            if (p1->data == p2->next->data) ///with p2 we compare only the elements which are after p1
            {
                del = p2->next; ///del is a pointer to the node which has to be deleted
                p2->next = p2->next->next; ///link to the next node
                free(del);
            }
            else p2 = p2->next; ///advance with p2
        }
        p1 = p1->next; ///advance with p1
        p2 = p1; ///we have to reset p2's value
    }
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
    ListT *A = createEmptySLL();
    A->first = A->last = createAndFillNode(17);
    insertAtRear(A,createAndFillNode(5));
    insertAtRear(A,createAndFillNode(5));
    insertAtRear(A,createAndFillNode(1));
    insertAtRear(A,createAndFillNode(13));
    insertAtRear(A,createAndFillNode(5));
    insertAtRear(A,createAndFillNode(3));
    insertAtRear(A,createAndFillNode(17));
    display(A);
    removeDuplicates(A);
    display(A);
    return 0;
}
