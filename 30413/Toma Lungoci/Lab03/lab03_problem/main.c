#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int app;
    char word[30];
    struct node *next;
    struct node *prev;
    int changed;
}NodeT;

typedef struct {
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

NodeT *createNode(char arr[])
{
    NodeT *p= (NodeT* )malloc(sizeof(NodeT));
    p->app=0;
    strcpy(p->word, arr);
    p->next=NULL;
    p->prev=NULL;
    return p;
}
int isEmpty (ListT *listPtr)
{
    if(listPtr->first==NULL)
        return 1;
    return 0;
}
int insertRear(ListT * listPtr, NodeT *p)
{
        if(listPtr)
        {
            if(isEmpty(listPtr))
            {
                listPtr->first=listPtr->last=p;
                p->prev=p->next=NULL;
            }
            else
            {
                p->prev=listPtr->last;
                listPtr->last->next=p;
                p->next=NULL;
                listPtr->last=p;

            }
            listPtr->count++;
            return 1;
        }
        return 0;
}
int insertFront(ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if(isEmpty(listPtr))
        {
            listPtr->first=p;
            listPtr->last=p;
            p->prev = p->next = NULL;
        }
        else
        {
            p->next=listPtr->first;
            listPtr->first->prev = p;
            p->prev = NULL;
            listPtr->first=p;
        }
        listPtr->count++;
        return 1;
    }
    return 0;
}
void insertBeforeKey(char givenword[], ListT *listPtr, NodeT *p)
{
    NodeT *q, *q1;
    q=listPtr->first;
    while( q!=NULL )
    {
        if(q->word == givenword )break;
        q1=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        if(q==listPtr->first)
        {
            insertFront(listPtr, p);
        }
        else
        {

            q1->next = p;
            p->prev = q1;
            p->next = q;
            q->prev = p;
        }
        listPtr->count++;
    }

}

void read(FILE *fi, ListT*listPtr, FILE *fo)
{

    char aux[100];

    while(fscanf(fi, "%s", aux)!=EOF)
    {

        int ok=0;
        NodeT *p;
        p=createNode(aux);
        if(aux[0]>=65 && aux[0]<=90)
        {
            p->word[0]=p->word[0]+32;
            p->word[strlen(aux)]='@';
            p->word[strlen(aux)+1]='\0';
        }

        if(isEmpty(listPtr))
        {
            p->app=1;
            insertRear(listPtr, p);
        }
        else
        {
            NodeT* q1=listPtr->first;
            while(q1!=NULL)
            {
                if((strcmp(p->word, q1->word)<0))
                {
                    insertBeforeKey(q1->word,listPtr, p);
                    p->app=1;
                    ok=1;
                    break;
                }
                else if(strcmp(p->word, q1->word)==0)
                {
                    q1->app++;
                    ok=1;
                    break;
                }
                q1=q1->next;
            }
        }
        if(ok==0)
        {
            insertRear(listPtr, p);
            p->app=1;
        }

    }
}
void printList(ListT *listPtr, FILE *fo)
{
    if(listPtr)
    {
        NodeT *p= listPtr->first;
        while(p!=NULL)
        {
            if(p->word[strlen(p->word)-1]=='@')
            {
                p->word[0]=p->word[0]-32;
                p->word[strlen(p->word)-1]='\0';
            }
            fprintf(fo, "%s :%d\n", p->word, p->app);
            p=p->next;
        }
    }
}
void printListRev(ListT *listPtr, FILE *fo)
{
        if(listPtr)
    {
        NodeT *p= listPtr->last;
        while(p!=NULL)
        {
            if(p->word[strlen(p->word)-1]=='@')
            {
                p->word[0]=p->word[0]-32;
                p->word[strlen(p->word)-1]='\0';
            }
            fprintf(fo, "%s :%d\n", p->word, p->app);
            p=p->prev;
        }
    }
}
int main(int argc, char *argv[])
{
    FILE *fi, *fo;
    for(int i=1; i<argc; i++)
        printf("%s\n", argv[i]);
    fi=fopen(argv[1], "r");
    fo=fopen(argv[2], "w");

    ListT *listPtr = (ListT *)malloc(sizeof(ListT));
    listPtr->count=0;
    listPtr->first=NULL;
    listPtr->last=NULL;

    read(fi,listPtr, fo);
    printList(listPtr, fo);
    fprintf(fo, "\n");
    printListRev(listPtr, fo);
    fclose(fi);
    fclose(fo);

    return 0;

}
