#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct node
{
    int data;
    struct node *last_next;
}NodeT;
typedef struct list
{
    NodeT *first;
    NodeT *last;
    int count;
}ListT;

ListT *createList()
{
    ListT *p=(ListT*)malloc(sizeof(ListT));
    if(p!=NULL)
    {
        p->first=NULL;
        p->last=NULL;
        p->count=0;
    }
    else exit(1);
}
NodeT *createNode(int val)
{
    NodeT *p;
    p=(NodeT*)malloc(sizeof(NodeT));
    if(p!=NULL)
    {
        p->data=val;
        p->last_next=NULL;
    }
    else exit(1);
}
NodeT *xor(NodeT *a, NodeT *b)
{
    return (NodeT*)((uintptr_t)a^(uintptr_t)b);
}
void insertAtFront(ListT *listPtr,NodeT *p)
{
    if(listPtr->count==0)
    {
        listPtr->first=p;
        listPtr->last=p;
    }
    else if(listPtr->count==1)
    {
        p->last_next=xor(NULL,listPtr->first);
        listPtr->first->last_next=xor(p,NULL);
        listPtr->first=p;

    }
    else
    {
        p->last_next=xor(NULL,listPtr->first);
        listPtr->first->last_next=xor(p,listPtr->first->last_next);
        listPtr->first=p;
    }
    listPtr->count++;
}
void insertAtRear(ListT *listPtr, NodeT *p)
{
    if(listPtr->count==0)
    {
        listPtr->first=p;
        listPtr->last=p;
    }
    else if(listPtr->count==1)
    {
        p->last_next=xor(NULL,listPtr->last);
        listPtr->first->last_next=xor(NULL,p);
        listPtr->last=p;
    }
    else
    {
        p->last_next=xor(listPtr->last,NULL);
        listPtr->last->last_next=xor(p,listPtr->last->last_next);
        listPtr->last=p;
    }
    listPtr->count++;
}
void insertBeforeKey(ListT *listPtr, int key, NodeT *p)
{
    NodeT *curr,*prev,*next;
    curr=listPtr->first;
    prev=NULL;
    while(curr!=NULL)
    {
        if(curr->data==key) break;
        next=xor(prev,curr->last_next);
        prev=curr;
        curr=next;
    }
    if(curr!=NULL)
    {
        if(curr==listPtr->first) insertAtFront(listPtr,p);
        else
        {
            p->last_next=xor(prev,curr);
            curr->last_next=xor(p,xor(prev,curr->last_next));
            prev->last_next=xor(p,xor(curr,prev->last_next));
        }
    }
    listPtr->count++;
}
void insertAfterKey(ListT *listPtr, int key, NodeT *p)
{
    NodeT *curr,*prev,*next;
    curr=listPtr->last;
    prev=NULL;
    while(curr!=NULL)
    {
        if(curr->data==key) break;
        next=xor(prev,curr->last_next);
        prev=curr;
        curr=next;
    }
    if(curr!=NULL)
    {
        if(curr==listPtr->last) insertAtRear(listPtr,p);
        else
        {
            p->last_next=xor(prev,curr);
            curr->last_next=xor(p,xor(curr->last_next,prev));
            prev->last_next=xor(p,xor(prev->last_next,curr));
        }
    }
    listPtr->count++;
}
void deleteFirst(ListT *listPtr)
{
    NodeT *p,*p1;
    if(listPtr->count==0) return;
    if(listPtr->count==1)
    {
        p=listPtr->first;
        listPtr->first=listPtr->last=NULL;
        free(p);
    }
    else
    {
        p=listPtr->first;
        p1=xor(p->last_next,NULL);
        listPtr->first=p1;
        listPtr->first->last_next=xor(NULL,xor(p1->last_next,p));
        free(p);
    }
    listPtr->count--;
}
void deleteLast(ListT *listPtr)
{
    NodeT *p,*p1;
    if(listPtr->count==0) return;
    if(listPtr->count==1)
    {
        p=listPtr->first;
        listPtr->first=listPtr->last=NULL;
        free(p);
    }
    else
    {
        p=listPtr->last;
        p1=xor(p->last_next,NULL);
        listPtr->last=p1;
        listPtr->last->last_next=xor(NULL,xor(p1->last_next,p));
        free(p);
    }
    listPtr->count--;
}
void deleteByKey(ListT *listPtr, int key)
{
    NodeT *curr,*prev,*next,*p1,*p2,*p;
    curr=listPtr->first;
    prev=NULL;
    while(curr!=NULL)
    {
        if(curr->data==key) break;
        next=xor(prev,curr->last_next);
        prev=curr;
        curr=next;
    }
    if(curr!=NULL)
    {
        if(listPtr->count==1)
        {
            p=listPtr->first;
            listPtr->first=listPtr->last=NULL;
            free(p);
        }
        else if(curr==listPtr->first)
        {
            deleteFirst(listPtr);
            return;
        }
        else if(curr==listPtr->last)
        {
           deleteLast(listPtr);
           return;
        }
        else
        {
            p1=xor(prev->last_next,curr);
            p2=xor(prev,curr->last_next);
            prev->last_next=xor(p1,p2);
            p2->last_next=xor(prev,xor(curr,p2->last_next));
            free(curr);
        }
        listPtr->count--;
    }
}
void printListA(ListT *listPtr)//print in ascending order
{
    NodeT *curr,*prev,*next;
    curr=listPtr->first;
    prev=NULL;
    while(curr!=NULL)
    {
        printf("%d ", curr->data);
        next=xor(prev,curr->last_next);
        prev=curr;
        curr=next;
    }
    printf("\n");
}
void printListD(ListT *listPtr)//print in descending order
{
    NodeT *curr,*prev,*next;
    curr=listPtr->last;
    prev=NULL;
    while(curr!=NULL)
    {
        printf("%d ",curr->data);
        next=xor(prev,curr->last_next);
        prev=curr;
        curr=next;
    }
    printf("\n");
}
void purgeList(ListT *listPtr)
{
    NodeT *curr, *prev,*next,*p;
    curr=listPtr->first;
    prev=NULL;
    while(curr!=NULL)
    {
        printf("suc ");
        p=curr;
        next=xor(prev,curr->last_next);
        prev=curr;
        curr=next;
        free(p);
    }
    listPtr->first=listPtr->last=NULL;
}
int main()
{
    ListT *listPtr;
    listPtr=createList();
    insertAtFront(listPtr,createNode(5));
    insertAtFront(listPtr,createNode(3));
    insertAtFront(listPtr,createNode(2));
    insertAtFront(listPtr,createNode(1));
    insertAtFront(listPtr,createNode(50));
    insertBeforeKey(listPtr,1,createNode(66));
    printListA(listPtr);
    //printf("%d %d\n",listPtr->first->data, listPtr->last->data);
    //insertBeforeKey(listPtr,5,createNode(7));
    //insertAfterKey(listPtr,50,createNode(19));
    //deleteByKey(listPtr,5);
    //deleteByKey(listPtr,50);
    //deleteByKey(listPtr,50);
    //printf("%d %d\n",listPtr->first->data, listPtr->last->data);
    //printf("%d ",listPtr->count);
    printListA(listPtr);
    purgeList(listPtr);
    printListD(listPtr);
    free(listPtr);
    return 0;
}
