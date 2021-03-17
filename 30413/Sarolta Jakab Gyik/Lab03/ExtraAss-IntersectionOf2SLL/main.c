/*Write a function that has as parameters two SLL and returns the intersection node if they intersect,
"NULL" otherwise*/

#include <stdio.h>
#include <stdlib.h>
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
int isEmpty( ListT *listPtr)
{
    if((listPtr->first == NULL) && (listPtr->last == NULL))
        return 1;
    return 0;
}
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
NodeT *intersection(ListT *firstList, ListT *secondList)
{
    NodeT *p;
    NodeT *q;
    p = firstList->first;
    while(p != NULL)
    {
        q = secondList->first;
        while(q!=NULL)
        {
            if(q->key == p->key)
                return q;
            q = q->next;
        }
        p = p->next;
    }
    return NULL;
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
void print(ListT *myList)
{
    if(myList->count == 0 && myList ->first == NULL && myList -> last == NULL)
        printf(" none");
    else
    {
        NodeT *r = myList->first;
        while(r != NULL)
        {
            printf("%d ", r->key);
            r = r -> next;
        }
    }
     printf("\n");
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
    FILE* f=fopen("in.txt", "r");
    FILE* g=fopen("in2.txt", "r");
    ListT *firstList;
    firstList = createEmptySLL();
    ListT *secondList;
    secondList = createEmptySLL();
    int key;
    NodeT *p;
    while(fscanf(f, "%d", &key) != EOF)
    {

        p = createSLLNode(key);
        int x = insertAtFront(firstList, p);
        if(!x)
            printf("Node not inserted");
        printf("%d\n", key);
    }
    while(fscanf(g, "%d", &key) != EOF)
    {

        p = createSLLNode(key);
        int x = insertAtFront(secondList, p);
        if(!x)
            printf("Node not inserted");
    }
    print(firstList);
    print(secondList);
    p = intersection(firstList, secondList);
    if(!p)
        printf("The lists do not intersect");
    else
    printf("The intersection is:%d", p->key);
    fclose(f);
    fclose(g);
    purge(firstList);
    purge(secondList);
    return 0;
}
