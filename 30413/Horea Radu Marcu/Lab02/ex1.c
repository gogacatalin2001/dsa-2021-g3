#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *next;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

ListT *createEmptySLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if (p)
    {
        p->key = key;
        p->next = NULL;
    }
    return p;
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if(listPtr->count==0)
        {
            listPtr->first = p;
        }
        else
        {
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

int find(ListT *listPtr, int givenKey)
{
    NodeT *p;
    p = listPtr->first;
    while(p != NULL)
    {
        if(p->key == givenKey) return 1;
        else p = p->next;
    }
    return 0;
}
NodeT *deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *q, *q1;
    q1=NULL;
    q=listPtr->first;
    while(q!=NULL)
    {
        if(q->key==givenKey) break;
        q1=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        if(q==listPtr->first)
        {
            listPtr->first=listPtr->first->next;
            if(listPtr->first==NULL) listPtr->last=NULL;
        }
        else
        {
            q1->next=q->next;
            if(q==listPtr->last) listPtr->last=q1;
        }
        return q;
    }
    return NULL;
}
int main()
{
    ListT *garage=createEmptySLL();
    ListT *road=createEmptySLL();
    FILE *f=fopen("in.txt","r");
    char *cuv=(char*)malloc(5*sizeof(char));
    while(fscanf(f,"%s",cuv)==1)
    {
        int x=cuv[2]-'0';
        if(cuv[3]>='0' && cuv[3]<='9') x=x*10+(cuv[3]-'0');
        if(cuv[0]=='R')
        {
            NodeT *p=createSLLNode(x);
            insertAtRear(road, p);
        }
        if(cuv[0]=='E')
        {
            NodeT *p=createSLLNode(x);
            int ok=find(road, x);
            if(ok==0) printf("error: %d not on road!\n", x);
            else
            {
                insertAtRear(garage, p);
                deleteByKey(road, x);
            }
        }
        if(cuv[0]=='X')
        {
            NodeT *p=createSLLNode(x);
            int ok=0;
            if(garage->last->key==x) ok=1;
            if(ok==0) printf("error: %d not at exit!\n", x);
            else
            {
                insertAtRear(road, p);
                deleteByKey(garage, x);
            }
        }
        if(cuv[0]=='S')
        {
            if(cuv[2]=='R')
            {
                printf("R: ");
                NodeT *p=road->first;
                if(p!=NULL)
                {
                while(p->next!=NULL) printf("%d ", p->key),p=p->next;
                printf("%d\n", road->last->key);
                }
                else printf("none\n");
            }
            if(cuv[2]=='G')
            {
                printf("G: ");
                NodeT *p=garage->first;
                if(p!=NULL)
                {
                    while(p->next!=NULL) printf("%d ", p->key),p=p->next;
                printf("%d\n", garage->last->key);
                }
                else printf("none\n");
            }
        }
    }
    return 0;
}
