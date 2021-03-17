#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_type
{
  int nr;
  char s[30];
  struct node_type *next;
  struct node_type *prev;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}DLListT;

DLListT *createEmptyDLL()
{
    DLListT *p=(DLListT*)malloc(sizeof(DLListT));
    if(p==NULL) exit(1);
    else
    {
        p->count=0;
        p->first=p->last=NULL;
    }
    return p;
}

NodeT *createNode(char s[])
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    if(p==NULL) exit(1);
    if(p!=NULL)
    {
        p->nr=1;
        strcpy(p->s,s);
        p->next=p->prev=NULL;;
    }
return p;
}
NodeT *traverseL(DLListT* listPtr, char *s)//compara sa vada daca exista returneaza null daca nu exista, p daca exista
{
    NodeT *p=listPtr->first;
    while(p!=NULL)
    {
        if(stricmp(p->s,s)==0) return p;
        p=p->next;
    }
    return NULL;
}
void insertAtRear(DLListT *listPtr, NodeT *p)
{
    if(listPtr->count==0)
    {
        listPtr->first=listPtr->last=p;
        p->prev=p->next=NULL;
    }
    else
    {
        listPtr->last->next=p;
        p->prev=listPtr->last;
        p->next=NULL;
        listPtr->last=p;
    }
    listPtr->count++;
}
void traverseA(DLListT *listPtr, NodeT *t)//traverseaza si adauga in ordine
{
    NodeT *q;
    q=listPtr->first;
    while(q!=NULL)
    {
        if(stricmp(t->s,q->s)<0) break;
        q=q->next;
    }
    if(q!=NULL)
    {
        listPtr->count++;
        if(q==listPtr->first)
        {
            t->next=listPtr->first;
            listPtr->first->prev=t;
            listPtr->first=t;
            t->prev=NULL;
        }
        else
        {
           q->prev->next=t;
           t->next=q;
           t->prev=q->prev;
           q->prev=t;
        }
        listPtr->count++;
    }
}
void purge(DLListT *listPtr)
{
    NodeT *p;
    p=listPtr->first;
    while(p!=NULL)
    {
        listPtr->first=listPtr->first->next;
        free(p);
        p=listPtr->first;
    }
    listPtr->last=NULL;
}
void print(DLListT *listPtr, char *argv)
{
    FILE *out=fopen(argv,"w");
    if(out==NULL) exit(1);
    NodeT *p=listPtr->first;
    while(p!=NULL)
    {
        fprintf(out,"%s:%d\n",p->s,p->nr);
        p=p->next;
    }
    fprintf(out,"------\n");
    p=listPtr->last;
    while(p!=NULL)
    {
        fprintf(out,"%s:%d\n",p->s,p->nr);
        p=p->prev;
    }
    fclose(out);
}
int main(int argc, char* argv[])
{
    DLListT *list=createEmptyDLL();
    FILE *in=fopen(argv[1],"r");
    if(in==NULL) exit(1);
    char s[50];
    NodeT *t;
    while(fscanf(in,"%s",s)==1)
    {
        if(list->count==0)
        {
            insertAtRear(list,createNode(s));
            continue;
        }
        t=traverseL(list,s);
        if(t!=NULL) t->nr++;
        else
        {
            if(stricmp(list->last->s,s)<0)
            {
                    insertAtRear(list,createNode(s));
                    continue;
            }
            traverseA(list,createNode(s));
        }
    }
    print(list,argv[2]);
    purge(list);
    free(list);
    fclose(in);
    return 0;
}
