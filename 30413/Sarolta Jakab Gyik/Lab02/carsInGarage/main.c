#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int truck_id;
    struct node *next;
} TrucksT;

typedef struct
{
    int count;
    TrucksT *first;
    TrucksT *last;
} ListT;

ListT *createEmptySLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

TrucksT *createSLLNode(int truck_id)
{
    TrucksT *p = (TrucksT *)malloc(sizeof(TrucksT));
    if (p)
    {
        p->truck_id = truck_id;
        p->next = NULL;
    }
    return p;
}
int isEmpty( ListT *listPtr)
{
    if((listPtr->first == NULL) && (listPtr->last == NULL))
        return 1;
    return 0;
}
int insertAtRear(ListT *listPtr, TrucksT *p)
{
    if (listPtr)
    {
        if (isEmpty(listPtr))
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
TrucksT *find(ListT *listPtr, int givenKey)
{
    TrucksT *p;
    p = listPtr->first;
    while ( p != NULL )
        if ( p->truck_id == givenKey )
            return p;
        else
            p = p->next;
    return NULL;
}
int deleteByKey(ListT *listPtr, int givenKey)
{
    TrucksT *q, *q1;
    q1 = NULL;
    q = listPtr->first;
    while ( q != NULL )
    {
        if ( q->truck_id == givenKey ) break;
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
        return 1;
    }
    return 0;
}
void writeTrucks(FILE *g, ListT *Road, char x)
{
    fprintf(g, "%c:", x);
    if(Road->count == 0 && Road ->first == NULL && Road -> last == NULL)
        fprintf(g, " none");
    else
    {
        TrucksT *r = Road->first;
        while(r != NULL)
        {
            fprintf(g, "%d ", r->truck_id);
            r = r -> next;
        }
    }
     fprintf(g, "\n");
}
void trucksOut(ListT *Road)
{
    TrucksT *p;
    while ( Road->first != NULL )
    {
        p = Road->first;
        Road->first = Road->first->next;
        free( p );
    }
    Road->last = NULL;
    Road->count = 0;
}
int main(int argc, char const *argv[])
{
    /*char file_name[20];
    sscanf(argv[1], "%s", &file_name);
    printf("%s\n", file_name);*/
    FILE *f = fopen ("in.txt", "r");
    FILE *g = fopen ("out.txt", "w");
    //LIFO principle - stack
    ListT *Road  = createEmptySLL();
    ListT *Garage = createEmptySLL();
    TrucksT *r;
    char line[6];
    while(fgets(line, sizeof(line), f))
    {
        printf("%s", line);
        int id;
        if(line[0] != 'S')
        {
            int j = 2;
            char truckId[5]= "";
            while((line[j]>='0') && (line[j]<='9'))
            {
                truckId[j-2] = line[j];
                j++;
            }
            printf("The trucks id is:%s\n", truckId);
            id = atoi(truckId);
            printf("The id is:%d\n", id);
        }
        if(line[0] == 'R')
        {
            r = createSLLNode(id);
            insertAtRear(Road, r);
        }
        else if(line[0] == 'X')
        {
            TrucksT *p;
            p = find(Garage, id);
            if(p == Garage -> last)
            {
                deleteByKey(Garage, id);
                p = createSLLNode(id);
                int x = insertAtRear(Road, p);
                if(!x)
                {
                    fprintf(g, "Error: cannot insert truck on road\n");
                    break;
                }
            }
            else if(p == 0)
            {
                fprintf(g, "Error: %d not in garage!\n", id);
            }
            else fprintf(g, "Error: %d not at exit!\n");
        }
        else if(line[0] == 'E')
        {
            TrucksT *p;
            p = find(Road, id);
            if(p == NULL)
                fprintf(g, "Error: %d not on road!\n", id);
            else
            {
                int i = deleteByKey(Road, id);
                createSLLNode(id);
                int x = insertAtRear(Garage, p);
                if(!x)
                {
                    fprintf(g, "Error: cannot insert truck in garage\n");
                    break;
                }
            }
        }
        else if(line[0] == 'S')
            if(line[2] == 'R')
                writeTrucks(g, Road, line[2]);
            else if(line[2] == 'G')
                writeTrucks(g, Garage, line[2]);
    }
    fclose(f);
    fclose(g);
    trucksOut(Road);
    trucksOut(Garage);
    return 0;
}
