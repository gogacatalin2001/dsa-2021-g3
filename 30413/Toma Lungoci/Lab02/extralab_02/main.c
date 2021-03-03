#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int key;
    struct node *next;
}node;

typedef struct {
    int count;
    node *first;
    node *last;
}ListT;

node *createNode(int key)
{
    node *p=malloc(sizeof(node));
    if(p)
    {
        p->key=key;
        p->next=NULL;
    }
    return p;
}
int isEmpty(ListT* listPtr)
{
    if(listPtr->first==NULL)
        return 1;
    return 0;
}

int addFront(ListT *listPtr,node *p)
{
    if(listPtr)
    {
        p->next=listPtr->first;
        if(isEmpty(listPtr))
        {
            listPtr->last=p;
        }
        listPtr->first=p;
        listPtr->count++;
        return 1;//succes
    }
    return 0;//failure
}


int addRear(ListT*listPtr, node*p)
{
    if (listPtr)
    {


        if(isEmpty(listPtr))
        {
            listPtr->first=p;
        }
        else
        {
            listPtr->last->next=p;
        }
        listPtr->last=p;
        listPtr->count++;
        return 1;//succes
    }
    return 0;//failure
}
node *deleteFirst(ListT *listPtr)
{
    node *p;
    if ( listPtr->first != NULL )
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free( p );
        listPtr->count--;
        if ( listPtr->first == NULL )
            listPtr->last = NULL;
        return p;
    }
    return NULL;
}
node *deleteLast(ListT*listPtr)
{
    node *q, *q1;
    q1=NULL;
    q=listPtr->first;
    if(q!=NULL){
        while (q!=listPtr->last)
        {
            q1=q;
            q=q->next;
        }
        if(q==listPtr->first)
        {
            listPtr->first=listPtr->last=NULL;
        }
        else{
            q1->next=NULL;
            listPtr->last=q1;
        }
        free(q);
    }
    return  q;
}

int deleteByKey(ListT*listPtr, int key)
{
    node *q, *q1;
    q1 = NULL;
    q =listPtr->first;

    while ( q != NULL )
    {
        if ( q->key == key ) break;
        q1 = q;
        q = q->next;
    }
    if ( q != NULL )
    {
        if ( q == listPtr->first )
        {
            listPtr->first = listPtr->first->next;
            free( q );
            if ( listPtr->first == NULL ) listPtr->last = NULL;
        }
        else
        {
            q1->next = q->next;
            if ( q == listPtr->last ) listPtr->last = q1;
            free( q );
        }
        listPtr->count--;
        return 1;
    }
    return 0;
}

void printList(ListT*listPtr, FILE* fo){
    if(isEmpty(listPtr))
        fprintf(fo, "list is empty!");
    node* ptrNodes= NULL;
    ptrNodes=listPtr->first;
    while(ptrNodes!=NULL)
    {
        fprintf(fo, "%d ", ptrNodes->key);
        ptrNodes=ptrNodes->next;
    }
    fprintf(fo, "\n");

}

void purge(ListT *listPtr)
{
    node* p;
    while(listPtr->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        free(p);
    }
    listPtr->last=NULL;
    listPtr->count=0;
}

void printfFirstx(ListT*listPtr, int x, FILE * fo){
    node* p=listPtr->first;
    if(x>=listPtr->count)
    {
        printList(listPtr, fo);
        return;
    }
    while(x!=0)
    {
        fprintf(fo, "%d ", p->key);
        p=p->next;
        x--;
    }
    fprintf(fo, "\n");
}
void printLastx(ListT *listPtr, int x, FILE *fo)
{
    int dif=listPtr->count - x;
    int aux=0;
    if(dif<=0)
    {
        printList(listPtr, fo);
        return;
    }
    node *p=listPtr->first;
    while(p!=NULL)
    {
        if(aux>=dif)
        {
            fprintf(fo, "%d ", p->key);
        }
        aux++;
        p=p->next;
    }
    fprintf(fo, "\n");
}

int main()
{
    ListT* listPtr=malloc(sizeof(listPtr));
    listPtr->count=0;
    listPtr->first=NULL;
    listPtr->last=NULL;
    char command[50];
    int key;
    FILE *fi, *fo;
    fi=fopen("in.txt", "r");
    fo=fopen("out.txt", "w");
    while(fscanf(fi, "%s %d", command, &key)!=EOF)
    {


        if(strcmp(command, "AF")==0)
        {
            node *p=createNode(key);
            addFront(listPtr, p);
        }
        else if(strcmp(command, "AL")==0)
        {
            node *p=createNode(key);
            addRear(listPtr, p);
        }
        else if(strcmp(command, "DF")==0)
        {
            deleteFirst(listPtr);
        }
        else if(strcmp(command, "DL")==0)
        {
            deleteLast(listPtr);
        }
        else if(strcmp(command, "PRINT_ALL")==0)
        {
            printList(listPtr,fo);
        }
        else if(strcmp(command, "DOOM_THE_LIST")==0)
        {
            purge(listPtr);
        }
        else if(strcmp(command, "DE")==0)
        {
            deleteByKey(listPtr, key);
        }
        else if(strcmp(command, "PRINT_F")==0)
        {
            printfFirstx(listPtr, key, fo);
        }
        else if(strcmp(command, "PRINT_L")==0)
        {
            printLastx(listPtr, key, fo);
        }
        else
            fprintf(fo, "command not found");

    }

    fclose(fi);
    fclose(fo);

    return 0;
}

