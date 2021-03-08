#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int apparitions;
    char word[20];
    struct node *next;
    struct node *prev;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

ListT *createEmptyDLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if(listPtr!=NULL)
    {
        listPtr->count=0;
        listPtr->first=listPtr->last=NULL;
    }
    return listPtr;
}

int isEmpty(ListT *listPtr)
{
    if(listPtr->first==NULL)
        return 1;
    return 0;
}

void insertAtRear(ListT *listPtr,char *word)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p!=NULL)
    {
        p->apparitions=1;
        strcpy(p->word,word);
        p->prev=p->next=NULL;
    }
    if(listPtr!=NULL)
    {
        if(isEmpty(listPtr)==1)
        {
            listPtr->first=listPtr->last=p;
            p->prev=p->next=NULL;
        }
        else
        {
            listPtr->last->next = p;
            p->prev = listPtr->last;
            listPtr->last = p;
            p->next = NULL;
        }
        listPtr->count++;
    }
    else
    {
        printf("Couldn't insert at rear");
        exit(-1);
    }
}

NodeT *findWord(ListT *listPtr,char *givenWord)
{
    NodeT *p;
    p=listPtr->first;
    while(p!=NULL)
    {
        if (strcmp(p->word, givenWord) == 0)
            return p;
        else
            p = p->next;
    }
    return NULL;
}

void swap(NodeT*x, NodeT*y)
{
    NodeT *aux;
    aux->apparitions=x->apparitions;
    strcpy(aux->word,x->word);
    x->apparitions=y->apparitions;
    strcpy(x->word,y->word);
    y->apparitions=aux->apparitions;
    strcpy(y->word,aux->word);
}

void purge(ListT *listPtr)
{
    NodeT *p;
    while (listPtr->first != NULL)
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free(p);
    }
    listPtr->last=NULL;
    listPtr->count=0;
}

void sort(ListT *listPtr)
{
    NodeT *p1;
    NodeT *p2;
    p1=listPtr->first;
    x:   p2=p1->next;
    while(p2->next!=NULL)
    {
        if(stricmp(p1->word,p2->word)<0)
            swap(p1,p2);
        p2=p2->next;
    }
    p1=p1->next;
    if(p1->next->next!=NULL)
        goto x;
}

void print(ListT *listPtr,FILE *g)
{
    NodeT *p = listPtr ->first;
    while(p->next!=NULL)
    {
        fprintf(g,"%s:%d\n",p->word,p->apparitions);
        p=p->next;
    }
    fprintf(g,"\n");
    fprintf(g,"\n");
}

void printInverse(ListT *listPtr,FILE *g)
{
    NodeT *p = listPtr ->last;
    while(p->prev!=NULL)
    {
        fprintf(g,"%s:%d\n",p->word,p->apparitions);
        p=p->prev;
    }
}

int main(int *argc, char *argv[])
{
    char s[100];
    FILE *f = fopen(argv[1],"r");
    FILE *g = fopen(argv[2],"w");
    ListT *listPtr = createEmptyDLL();
    while(fscanf(f,"%s",s)==1)
    {
        if(findWord(listPtr,s)!=NULL)
            findWord(listPtr,s)->apparitions++;
        else
        {
            insertAtRear(listPtr,s);
            listPtr->count++;
        }
    }
    sort(listPtr);
    print(listPtr,g);
    printInverse(listPtr,g);
    purge(listPtr);
    return 0;
}
//Process finished with exit code -1073741819 (0xC0000005)
//I have searched this code on the internet and there it says that
//it may be a pointer that has been overwritten or that i have been
//adressing something outside of allowed boundaries
//"In that case you point to a piece of memory that has not been allocated
// to your process and thus does and should generate access violation."
// still, i couldn't identify the problem. My guess is that the problem is
//at the function "swap" or "sort"