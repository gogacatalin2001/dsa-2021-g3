#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct truck {
    int id;
    struct truck* next;
}truck;

typedef struct{
       int count;
       truck* first;
       truck* last;
}ListT;

int isEmpty(ListT *listPtr)
{
    if(listPtr->first==NULL)
        return 1;
    return 0;
}
truck *createTruck(int id)
{
    truck* p=malloc(sizeof(truck));
    p->id=id;
    p->next=NULL;
    return p;
}
void addRear(ListT*listPtr, truck *p)
{
    if(isEmpty(listPtr))
    {
        listPtr->first=p;
    }
    else
    {
        listPtr->last->next=p;
    }
    listPtr->count++;
    listPtr->last=p;

}
truck *deleteFirst(ListT *listPtr)
{
    truck *p;
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
void out(ListT *listPtr, int id, FILE * fo)
{
    if(listPtr->first->id!=id)
        fprintf(fo, "%d not at exit\n", id);
    else
        deleteFirst(listPtr);
}
int deleteByKey(ListT*listPtr, int key)
{

    truck *q, *q1;
    q1 = NULL;
    q =listPtr->first;

    while ( q != NULL )
    {
        if ( q->id == key ) break;
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

void print(ListT *listPtr, FILE*fo)
{
    if(isEmpty(listPtr))
    {
        fprintf(fo, "none");
    }
    else
    {
        truck* q=listPtr->first;
        while(q!=NULL)
        {
            fprintf(fo, "%d ", q->id);
            q=q->next;
        }
    }
    fprintf(fo, "\n");
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
int checkRoad(ListT *listPtr, int id)
{
    truck* q=listPtr->first;
    while(q!=NULL)
    {
        if(q->id==id)
            return 1;
        q=q->next;
    }
    return 0;
}

void instructions(FILE *fi, FILE *fo, ListT *ptr, ListT *road)
{
    char c;
    char id[10];
    while(fscanf(fi, "%c(%s )", &c, id)!=EOF)
    {

        if(c=='R')
        {

            truck *p= createTruck(stringToInt(id));
            addRear(road, p);
        }
        else if(c=='E')
        {


            if(checkRoad(road, stringToInt(id))==0)
                fprintf(fo, " %d not on road.\n", stringToInt(id));
            else
            {
                truck *p=createTruck(stringToInt(id) );
                addRear(ptr, p);
                deleteByKey(road, stringToInt(id));
            }
        }
        else if(c=='X')
        {
            out(ptr, stringToInt(id), fo);
        }
        else if(c=='S')
        {
            if(strcmp(id, "R")==0)
            {
                fprintf(fo, "R:");print(road, fo);
            }
            else if(strcmp(id, "G")==0)
            {
                fprintf(fo, "G:");print(ptr, fo);
            }
        }
    }
}
int main(int argc,char *argv[])
{
    ListT* garage=malloc(sizeof(ListT));
    garage->count=0;
    garage->first=NULL;
    garage->last=NULL;

    ListT *road=malloc(sizeof(ListT));
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

    instructions(fi, fo, garage, road);
    purge(garage);
    purge(road);
    fclose(fi);
    fclose(fo);

    return 0;
}
