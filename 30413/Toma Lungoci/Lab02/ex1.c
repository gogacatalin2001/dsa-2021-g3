#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct truck{
    int truckID;
    struct node *next;
}truck;

typedef struct {
    int count;
    truck *first;
    truck *last;
}ListT;

truck *addTruck(int truckID){
    truck *p=malloc(sizeof(truck));
    p->truckID=truckID;
    p->next=NULL;
    return p;
}

int isEmpty (ListT *ptr)
{
    if(ptr->first==NULL)
        return 1;
    return 0;
}

void push(ListT *ptr, truck *p ){
    if(isEmpty(ptr))
    {
        ptr->first=p;

    }
    else
    {
        ptr->last->next=p;
    }
    ptr->last=p;
    ptr->count++;
}

truck *deleteLast(ListT*listPtr)
{
    truck *q, *q1;
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

truck* top(ListT* ptr )
{
    truck *top=ptr->last;
    return top;
}
void pop(ListT *ptr, int truckId, FILE *fo)
{
    if(truckId!=top(ptr)->truckID)
    {
        fprintf(fo, "%d not at exit!\n", truckId);
    }
    else
    {
        deleteLast(ptr);
    }
}
void print(ListT *ptr, FILE *fo)
{
    if(isEmpty(ptr))
    {
        fprintf(fo, " none");
    }
    else
    {
        truck *p= ptr->first;
        while(p!=NULL)
        {
            fprintf(fo, "%d ", p->truckID);
            p=p->next;
        }
    }
    fprintf(fo, "\n");

}
int deleteByKey(ListT*listPtr, int key)
{

    truck *q, *q1;
    q1 = NULL;
    q =listPtr->first;

    while ( q != NULL )
    {
        if ( q->truckID == key ) break;
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
int checkRoad(ListT *listPtr, int id)
{
    truck* q=listPtr->first;
    while(q!=NULL)
    {
        if(q->truckID==id)
            return 1;
        q=q->next;
    }
    return 0;
}
void purge(ListT *listPtr)
{
    truck* p;
    while(listPtr->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        free(p);
    }
    listPtr->last=NULL;
    listPtr->count=0;
}
int stringToInt(char number[])
{
    int i, integer=0, j=1;

    for(i=0; i<strlen(number); i++)
    {
        integer=integer*10+(number[i]-'0');
    }
    return integer;
}
void instructions(FILE *fi, FILE *fo, ListT *ptr, ListT *road)
{
    char c;
    char id[10];
    while(fscanf(fi, "%c(%s )", &c, id)!=EOF)
    {

        if(c=='R')
        {
            truck *p= addTruck(stringToInt(id));
            push(road, p);
        }
        else if(c=='E')
        {
            //truck *p= select(road, stringToInt(id));

            if(checkRoad(road, stringToInt(id))==0)
                fprintf(fo, " %d not on road.\n", stringToInt(id));
            else
            {
                truck* p=addTruck(stringToInt(id));
                push(ptr, p);
                deleteByKey(road, stringToInt(id));
            }
        }
        else if(c=='X')
        {
            pop(ptr, stringToInt(id), fo);
        }
        else if(c=='S')
        {
            if(strcmp(id, "R")==0)
            {
                fprintf(fo,"R:");print(road, fo);
            }
            else if(strcmp(id, "G")==0)
            {
                fprintf(fo,"G:");print(ptr, fo);
            }

        }
    }
}
int main(int argc, char*argv[])
{
    ListT *ptr=malloc(sizeof(ListT));//garage
    ptr->count=0;
    ptr->first=NULL;
    ptr->last=NULL;

    ListT *road=malloc(sizeof(ListT));//road
    road->count=0;
    road->first=NULL;
    road->last=NULL;

    FILE *fi, *fo;
    fi=fopen(argv[1], "r");
    fo=fopen(argv[2], "w");
    for(int i=0; i<argc; i++)
    {
        printf("%s\n", argv[i]);//checking if read correctly.
    }
    instructions(fi, fo, ptr, road);

    purge(ptr);
    purge(road);
    fclose(fi);
    fclose(fo);
    return 0;
}
