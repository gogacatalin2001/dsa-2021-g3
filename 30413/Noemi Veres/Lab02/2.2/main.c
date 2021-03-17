#include <stdio.h>
#include <stdlib.h>
FILE *openCheck (const char *path, const char *mode, int i)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        puts("cannot open the file");
        exit(i);
    }
    return pf;
}
/// node type
typedef struct node
{
    unsigned int truck_id;
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
        listPtr -> count = 0;
        listPtr -> first = listPtr -> last = NULL;
    }
    return listPtr;
}
/// create and fill a node
NodeT *createAndFillNode(unsigned int truck_id)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p -> truck_id = truck_id;
        p -> next = NULL;
    }
    return p;
}
/// check if the list is non-empty
int isEmpty (ListT *listPtr)
{
    if (listPtr -> count == 0 && listPtr -> first == NULL && listPtr -> last == NULL) return 1;
    return 0;
}
/// inserting a node at the end - garage
void insertAtRear (ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if (isEmpty(listPtr))
            listPtr -> first = p;
        else listPtr -> last -> next = p;
        listPtr -> last = p;
        listPtr -> count++;
    }
}
/// inserting a node at the beginning - road
void insertAtFront (ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        p -> next = listPtr -> first;
        if (isEmpty(listPtr))
            listPtr -> last = p;
        listPtr -> first = p;
        listPtr -> count++;
    }
}
/// removing the first node - FIFO - garage
NodeT *deleteFirst (ListT *listPtr)
{
    NodeT *p;
    if (listPtr -> first != NULL)
    {
        p = listPtr -> first;
        listPtr -> first = listPtr -> first -> next;
    listPtr -> count--;
    if (listPtr -> first == NULL)
        listPtr -> last = NULL;
    return p;
    }
    return NULL;
}
/// removing a node by a given id - road
void deleteById (ListT *listPtr, unsigned int given_id)
{
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr -> first;
    while (q != NULL)
    {
        if (q -> truck_id == given_id) break;
        q1 = q;
        q = q -> next;
    }
    if (q != NULL)
    {
        if (q == listPtr -> first)
        {
            listPtr -> first = listPtr -> first -> next;
            if (listPtr -> first == NULL)
                listPtr -> last = NULL;
        }
        else
        {
            q1 -> next = q -> next;
            if (q == listPtr -> last)
                listPtr -> last = q1;
        }
        listPtr -> count--;
    }
}
/// find a truck with a given id
NodeT *find(ListT *listPtr, unsigned int given_id)
{
    NodeT *p;
    p = listPtr -> first;
    while (p != NULL)
    {
        if (p -> truck_id == given_id) return p;
        else p = p -> next;
    }
    return NULL;
}
/// show trucks
void display (ListT *listPtr, char ch, FILE *pf)
{
    fprintf(pf,"%c:", ch);
    if (listPtr -> count == 0 && listPtr -> first == NULL && listPtr -> last == NULL)
        fprintf(pf," none");
    else
    {
        NodeT *p = listPtr -> first;
        while (p != NULL)
        {
            fprintf(pf," %u", p -> truck_id);
            p = p -> next;
        }
    }
    fprintf(pf,"\n");
}
unsigned int extractID (FILE *pf)
{
    unsigned int id = 0;
    int ch = fgetc(pf);
    ch = fgetc(pf);
    while (ch != ')')
    {
        id = id*10 + (ch - '0');
        ch = fgetc(pf);
    }
    return id;
}
int main(int argc, char *argv[])
{
    FILE *pIn = openCheck(argv[1], "r", 1);
    FILE *pOut = openCheck(argv[2], "w", 2);
    ListT *G = NULL, *R = NULL;
    R = createEmptySLL();
    G = createEmptySLL();
    int ch = fgetc(pIn);
    unsigned int truck_id;
    NodeT *new_tr, *address;
    while (ch != EOF)
    {
        switch (ch)
        {
        case 'R':
            truck_id = extractID(pIn);
            new_tr = createAndFillNode(truck_id);
            insertAtRear(R,new_tr);
            break;
        case 'E':
            truck_id = extractID(pIn);
            address = find(R,truck_id);
            if (address == NULL)
            {
                fprintf(pOut, "error: %u not on road!\n", truck_id);
                break;
            }
            else
            {
                new_tr = createAndFillNode(address -> truck_id);
                insertAtRear(G,new_tr);
                deleteById(R,truck_id);
            }
            break;
        case 'X':
            truck_id = extractID(pIn);
            address = find(G,truck_id);
            if (address == G -> first)
            {
                deleteFirst(G);
                new_tr = createAndFillNode(address -> truck_id);
                insertAtFront(R,new_tr);
            }
            else fprintf(pOut,"error: %u not at exit!\n", address -> truck_id);
            break;
        case 'S':
            ch = fgetc(pIn);
            ch = fgetc(pIn);
            if (ch == 'R')
                display(R,'R',pOut);
            else display(G,'G',pOut);
            break;
        }
        ch = fgetc(pIn);
    }
    fclose(pIn);
    fclose(pOut);
    return 0;
}
