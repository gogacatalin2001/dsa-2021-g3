#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
}NodeT;
typedef struct header
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

ListT *createEmptySLL()
{
    ListT *p=(ListT*)malloc(sizeof(ListT));
    if(p!=NULL)
    {
        p->count=0;
        p->first=NULL;
        p->last=NULL;
    }
    else exit(1);
    return p;
}
NodeT *createSLLNode(int key)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    if(p!=NULL)
    {
        p->data=key;
        p->next=NULL;
    }
    else exit(1);
    return p;
}
void addFirst(NodeT *p, ListT *listPtr)
{
    p->next=listPtr->first;
    if(listPtr->first==NULL && listPtr->last==NULL)
        listPtr->last=p;
    listPtr->first=p;
    listPtr->count++;
}
void addLast(NodeT *p, ListT *listPtr)
{
    if(listPtr->first==NULL && listPtr->last==NULL)
        listPtr->first=p;
    else listPtr->last->next=p;
    listPtr->last=p;
    listPtr->count++;
}
void deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if(listPtr->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        free(p);
        listPtr->count--;
        if(listPtr->first==NULL)
            listPtr->last=NULL;
    }
}
void deleteLast(ListT *listPtr)
{
    NodeT *q, *q1;
    q1=NULL;
    q=listPtr->first;
    if(q!=NULL)
    {
        while(q!=listPtr->last)
        {
            q1=q;
            q=q->next;
        }
    if(q==listPtr->first)
        listPtr->first=listPtr->last=NULL;
    else
    {
        q1->next=NULL;
        listPtr->last=q1;
    }
    free(q);
    listPtr->count--;
    }
}
void purge(ListT *listPtr)
{
    NodeT *p;
    while(listPtr->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        free(p);
    }
    listPtr->last=NULL;
    listPtr->count=0;
}
void deleteElement(ListT *listPtr, int key)
{
    NodeT *q, *q1;
    q1=NULL;
    q=listPtr->first;
    while(q!=NULL)
    {
        if(q->data==key) break;
        q1=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        if(q==listPtr->first)
        {
            listPtr->first=listPtr->first->next;
            listPtr->count--;
            free(q);
            if(listPtr->first==NULL) listPtr->last=NULL;
        }
        else
        {
            q1->next=q->next;
            if(q==listPtr->last) listPtr->last=q1;
            listPtr->count--;
            free(q);
        }
    }
}
void printAll(ListT *listPtr)
{
    FILE *out;
    out=fopen("output.txt","a");
    NodeT *p=listPtr->first;
    while(p!=NULL)
    {
        fprintf(out,"%d ",p->data);
        p=p->next;
    }
    fprintf(out,"\n");
    fclose(out);
}
void printFirst(ListT *listPtr,int nr)
{
    NodeT *p=listPtr->first;
    FILE *out;
    out=fopen("output.txt","a");
    while(p!=NULL && nr!=0)
    {
        fprintf(out,"%d ",p->data);
        p=p->next;
        nr--;
    }
    fprintf(out,"\n");
    fclose(out);
}
void printLast(ListT *listPtr, int nr)
{
    int cont1=0, cont2=listPtr->count-nr;
    if(nr>=listPtr->count) {printAll(listPtr);
                  return;}
    else
    {
        NodeT *p=listPtr->first;
        while(cont1!=cont2)
        {
            p=p->next;
            cont1++;
        }
        FILE *out;
        out=fopen("output.txt","a");
        while(p!=NULL)
        {
            fprintf(out,"%d ",p->data);
            p=p->next;
        }
        fprintf(out,"\n");
        fclose(out);
    }
}
int main()
{
    ListT *listPtr;
    listPtr=createEmptySLL();
    FILE *input, *output;
    input=fopen("input.txt","r");
    output=fopen("output.txt","w");
    fclose(output);
    if(input==NULL)
    {
        printf("error");
        exit(1);
    }
    char s[50],s2[50];
    int d;
    while(fgets(s,50,input)!=NULL)
    {
        if(s[strlen(s)-1]=='\n') s[strlen(s)-1]='\0';
        if(strcmp(s,"DOOM_THE_LIST")==0)
        {
           purge(listPtr);
           continue;
        }
        if(strcmp(s,"PRINT_ALL")==0)
        {
            printAll(listPtr);
            continue;
        }
        if(strcmp(s,"DL")==0)
        {
            deleteLast(listPtr);
            continue;
        }
        if(strcmp(s,"DF")==0)
        {
            deleteFirst(listPtr);
            continue;
        }
        sscanf(s,"%s %d",s2,&d);
        if(strcmp(s2,"PRINT_F")==0) printFirst(listPtr,d);
        if(strcmp(s2,"PRINT_L")==0) printLast(listPtr,d);
        if(strcmp(s2,"AF")==0) addFirst(createSLLNode(d),listPtr);
        if(strcmp(s2,"AL")==0) addLast(createSLLNode(d),listPtr);
        if(strcmp(s2,"DE")==0) deleteElement(listPtr,d);
    }
fclose(input);
purge(listPtr);
free(listPtr);
    return 0;
}
