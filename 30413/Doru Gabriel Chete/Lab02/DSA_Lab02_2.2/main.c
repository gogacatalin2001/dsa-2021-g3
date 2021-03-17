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

TruckT *deleteLast(ListT *listPtr)
{
    TruckT *t, *t1;
    t1 = NULL;
    t = listPtr->first;
    if(t != NULL)
    {
        while(t != listPtr->last)
        {
            t1 = t;
            t = t->next;
        }
        if(t == listPtr->first)
        {
            listPtr->first = listPtr->last = NULL;
        }
        else
        {
            t1->next = NULL;
            listPtr->last = t1;
        }
        free(t);
    }
    return t;
}



int main(char argc, char *argv[])
{
    //For this version of the problem we have the same solution except now both the road and the garage are queues
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
            insertAtFront(Road, &t);     // add it to the road;
        }
        else if(command[0] == 'E')
        {
            TruckT t;
            t.truck_id = (int)(command[2]) - 48; // get the index of the truck to be added to the road
            if(t.truck_id != Road->last->truck_id)
            {
                fprintf(fo, "error\n");
            }
            else
            {
                deleteLast(Road); // delete the first truck that got on the road
                insertAtFront(Garage, &t); // add it to the garage
            }
            deleteTruck(Road, t.truck_id);      // delete the truck from the road
            insertAtFront(Garage, &t);         // put the truck in the garage
        }
        else if(command[0] == 'X')
        {
            if(Garage->last->truck_id != ((int)command[2] - 48)) // if the truck is not the first one entered in the garage
            {
                fprintf(fo, "error: ");
                fprintf(fo, "%d", ((int)command[2] - 48));
                fprintf(fo, " not at exit!\n");
            }
            else
            {
                insertAtFront(Road, Garage->last); // the first truck that got in the garage gets out
                deleteLast(Garage);

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
}
