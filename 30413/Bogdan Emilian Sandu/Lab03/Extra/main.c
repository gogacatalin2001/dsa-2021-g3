#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
}NodeT;

typedef struct
{
    NodeT *first;
    NodeT *last;
}ListT;

NodeT *createNode(int val)
{
    NodeT *p;
    p=(NodeT*)malloc(sizeof(NodeT));
    if(p==NULL) exit(1);
    p->val=val;
    p->next=NULL;
    return p;
}

ListT *createList()
{
    ListT *listPtr;
    listPtr=(ListT*)malloc(sizeof(ListT));
    if(listPtr==NULL) exit(1);
    listPtr->first=listPtr->last=NULL;
    return listPtr;
}
void insertFront(NodeT *p,ListT *listPtr)
{
    if(listPtr->first==NULL)
    {
        listPtr->first=listPtr->last=p;
        p->next=NULL;
    }
    else
    {
        p->next=listPtr->first;
        listPtr->first=p;
    }
}
NodeT *interNode(ListT *listPtr1, ListT *listPtr2)//functia pentru intersectie
{
    NodeT *q1,*q2;
    if(listPtr1->first==NULL || listPtr2->first==NULL) return NULL;
    q1=listPtr1->first;
    while(q1!=NULL)
    {
     q2=listPtr2->first;
     while(q2!=NULL)
     {
       if(q2->val==q1->val) return q2;
       q2=q2->next;
     }
     q1=q1->next;
    }
}
void removeDups(ListT *listPtr)//functia pentru stergere a duplicatelor
{
    NodeT *q1, *q2,*q3;
    if(listPtr->first==NULL) return;
    if(listPtr->first==listPtr->last) return;
    q1=listPtr->first;
    while(q1!=NULL)
    {
        q2=q1->next;
        q3=q1;
        while(q2!=NULL)
        {
            if(q2->val==q1->val)
            {
                if(q2->next==NULL)
                {
                    q3->next=NULL;
                    listPtr->last=q3;
                    free(q2);
                    break;
                }
                else
                {
                   q3->next=q2->next;
                   free(q2);
                   q2=q3->next;
                   continue;
                }
            }
        q3=q2;
        q2=q2->next;
        }
        q1=q1->next;
    }
}

void printList(ListT *listPtr)
{
    if(listPtr->first==NULL)
        {
        printf("Empty list\n");
        return;
        }
    NodeT *p=listPtr->first;
    while(p!=NULL)
    {
        printf("%d\n",p->val);
        p=p->next;
    }
}

int main()
{
    ListT *listPtr1, *listPtr2;
    listPtr1=createList();
    listPtr2=createList();
    insertFront(createNode(5),listPtr1);
    insertFront(createNode(3),listPtr1);
    insertFront(createNode(3),listPtr1);
    insertFront(createNode(6),listPtr1);
    insertFront(createNode(5),listPtr1);
    insertFront(createNode(6),listPtr1);
    insertFront(createNode(8),listPtr1);
    insertFront(createNode(3),listPtr1);
    ///---
    /*insertFront(createNode(6),listPtr2);
    insertFront(createNode(8),listPtr2);
    insertFront(createNode(0),listPtr2);
    NodeT *p=interNode(listPtr1,listPtr2);
    removeDups(listPtr1);
    if(p!=NULL) printf("%d",p->val);
    else printf("nu exista");*/
    removeDups(listPtr1);
    printList(listPtr1);

    return 0;
}
