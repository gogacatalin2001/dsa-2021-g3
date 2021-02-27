#include <stdio.h>
#include <stdlib.h>

typedef struct truck
{
    int truck_id; // the index of the truck
    struct truck *next;
} TruckT;

typedef struct
{
    int count;
    TruckT *first;
    TruckT *last;
} ListT;

ListT *createEmptySLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = NULL;
        listPtr->last = NULL;
    }
    return listPtr;
}

int isEmpty(ListT* listPtr)
{
    if(listPtr->first == NULL)
    {
        return 1;
    }
    return 0;
}

int insertAtFront(ListT *listPtr, TruckT *t)
{
    if(listPtr)
    {
        t->next = listPtr->first;
        if(isEmpty(listPtr))
        {
            listPtr->last = t;
        }
        listPtr->first = t;
        listPtr->count++;
        return 1;
    }
    return 0;
}

int deleteTruck(ListT *listPtr, int givenTruck_id)
{
    TruckT *t, *t1;
    t1 = NULL;
    t = listPtr->first;
    while(t != NULL)
    {
        if(t->truck_id == givenTruck_id)
        {
            break;
        }
        t1 = t;
        t = t->next;
    }
    if(t != NULL)
    {
        if(t == listPtr->first)
        {
            listPtr->first = listPtr->first->next;
            free(t);
            if(listPtr->first = NULL)
            {
                listPtr->last = NULL;
            }
        }
        else
        {
            t1->next = t->next;
                       if(t == listPtr->last)
            {
                listPtr->last = t1;
            }
            free(t);
        }
        return 1;
    }
    return 0;
}

TruckT *deleteFirst(ListT *listPtr)
{
    TruckT *t;
    if(listPtr->first != NULL)
    {
        t = listPtr->first;
        listPtr->first = listPtr->first->next;
        free(t);
        listPtr->count--;
        if(listPtr->first == NULL)
        {
            listPtr->last == NULL;
        }
        return t;
    }
    return NULL;
}



int main(char argc, char *argv[])
{
    FILE  *fo, *fi;
    char command[10];
    fi = fopen(argv[1], "r"); //    argv[1] must be the name of the input file      //
    fo = fopen(argv[2], "w"); //   argv[2] must be the name of the output file       //
    ListT* Road = createEmptySLL();   // create SLL for the road
    ListT* Garage = createEmptySLL(); // create SLL for the garage
    while(fscanf(fi, "%s", command) != EOF)     // reading the commands
    {
        if(command[0] == 'R')
        {
            TruckT t;
            t.truck_id = (int)(command[2]) - 48; // get the index of the truck to be added to the road
            insertAtFront(Road, &t);
        }
        else if(command[0] == 'E')
        {
            TruckT t;
            t.truck_id = (int)(command[2]) - 48; // get the index of the truck that enters the garage
            deleteTruck(Road, t.truck_id);      // delete the truck from the road
            insertAtFront(Garage, &t);         // put the truck in the garage
        }
        else if(command[0] == 'X')
        {
            if(Garage->first->truck_id != ((int)command[2] - 48)) // if the truck is not the last one entered in the garage
            {
                fprintf(fo, "error: ");
                fprintf(fo, "%d", ((int)command[2] - 48));
                fprintf(fo, " not at exit!\n");
            }
            else
            {
                insertAtFront(Road, Garage->first);
                deleteFirst(Garage);
            }

        }
        else if(command[0] == 'S')
        {
            if(command[2] == 'R')  //if the trucks on the road have to be printed
            {
                TruckT* p;
                p = Road->first;
                while(p != NULL)
                {
                    printf(" %d ", p->truck_id);
                    p = p->next;
                }
                printf("\n");
                free(p);
            }
            else if(command[2] == 'G')    // if the trucks in the garage have to be printed
            {
                TruckT* p;
                p = Garage->first;
                while(p != NULL)
                {
                    printf(" %d", p->truck_id);
                    p = p->next;

                }
                printf("\n");
                free(p);
            }
        }
    }
    fclose(fi);
    fclose(fo);
    return 0;
}
