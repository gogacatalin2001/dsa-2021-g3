#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct truck {
    int ID;
    struct truck *next;
} TruckT;

typedef struct {
    int count;
    TruckT *first;
    TruckT *last;
} ListT;

int countLines(FILE *filePtr)   /// returns number of lines in file pointed to by filePtr
{
    int lines = 0;
    for(;;) {
        char c = fgetc(filePtr);
        if(c == EOF) {
            lines++;
            break;
        }
        else if (c == '\n') {
            lines++;
        }
    }
    rewind(filePtr);
    return lines;
}

ListT *createEmptySLL()
{
    ListT *listPtr = (ListT*) malloc (sizeof(ListT));
    if(listPtr) {
        listPtr -> count = 0;
        listPtr -> first = listPtr -> last = NULL;
    }
    return listPtr;
}

TruckT *createSLLTruck(int ID)
{
    TruckT *t = (TruckT*) malloc (sizeof(TruckT));
    if(t) {
        t -> ID = ID;
        t -> next = NULL;
    }
    return t;
}

bool isEmpty(ListT *listPtr)
{
    if(listPtr -> count == 0 && listPtr -> first == NULL && listPtr -> last == NULL) {
        return 1;
    }
    return 0;
}

bool insertAtRear(ListT *listPtr, TruckT *t)
{
    if(listPtr) {
        if(isEmpty(listPtr)) {
            listPtr -> first = t;
        }
        else {
            listPtr -> last -> next = t;
        }
        listPtr -> last = t;
        listPtr -> count++;
        return 1;
    }
    return 0;
}

int deleteByID(ListT *listPtr, int givenID)
{
    TruckT *q, *q1;
    q1 = NULL;
    q = listPtr -> first;
    while (q != NULL) {
        if( q -> ID == givenID ) {
            break;
        }
        q1 = q;
        q = q -> next;
    }
    if( q != NULL ) {
        if( q == listPtr -> first ) {
            listPtr -> first = listPtr -> first -> next;
            free(q);
            if(listPtr -> first == NULL){
                listPtr -> last = NULL;
            }
        }
        else {
            q1 -> next = q -> next;
            if(q == listPtr -> last) {
                listPtr -> last = q1;
            }
            free(q);
        }
        listPtr -> count--;
        return 1;
    }
    return 0;
}

TruckT *findTruck(ListT *listPtr, int givenID)
{
    TruckT *t;
    t = listPtr -> first;
    while (t != NULL) {
        if( t -> ID == givenID ) {
            return t;
        }
        else {
            t = t -> next;
        }
    }
    return NULL;
}

bool insertAtFront(ListT *listPtr, TruckT *t)
{
    if (listPtr) {
        t -> next = listPtr -> first;
        if( isEmpty(listPtr) ) {
            listPtr -> last = t;
        }
        listPtr -> first = t;
        listPtr -> count++;
        return 1;
    }
    return 0;
}

void displayID(ListT *listPtr)
{

}

int main()
{
    FILE *filePtr;
    filePtr = fopen("input.txt", "r");

    int i, auxID;
    int numberLines = countLines(filePtr);

    ListT *roadList = createEmptySLL();
    ListT *garageList = createEmptySLL();

    for(i = 0; i < numberLines; i++)    /// for every line i read the command and then the truck ID = auxID
    {                                   /// or 'G'/'R' when c == 'S'
        char c = fgetc(filePtr);
        fgetc(filePtr); /// to pass '('

        if(c == 'R'){
        /// place truck on road:
        /// create truck with ID auxID
        /// add that truck at the rear of roadList
            fscanf(filePtr, "%d", &auxID);
            printf("%c(%d)\n", c, auxID);
            if( !insertAtRear(roadList, createSLLTruck(auxID)) )
                printf("error");
            else printf("truck with id %d was introduced in R\n", roadList->last->ID);
        }

        else if(c == 'E'){
        /// truck enters the garage:
        /// find truck with ID = auxID in roadList
            /// if NULL display error:_auxID_not_on_road!
            /// if found add that truck in front of garageList, delete that truck from roadList
            fscanf(filePtr, "%d", &auxID);
            printf("%c(%d)\n", c, auxID);
            TruckT *auxT = findTruck(roadList, auxID);
            if( auxT == NULL ) {
                printf("error:_%d_not_on_road!\n", auxID);  /// says truck with id 10 not on the road i really
                                                            /// can't figure out why
            }
            else {
                if( !insertAtFront(garageList, auxT) ) {
                    printf("error");
                }
                else printf("truck with id %d entered the garage\n", garageList->first->ID);
                if( !deleteByID(roadList, auxID) ) {
                    printf("error");
                }
                else printf("truck with id %d removed from road\n", auxID);
            }
        }

        else if(c == 'X'){
            /// truck exits the garage:
            /// check if truck with auxID is the first of garageList
                /// if yes, add that truck at rear of roadList, remove truck from the front of garageList
                /// if not, display error:_auxID_not_at_exit!
            fscanf(filePtr, "%d", &auxID);
            printf("%c(%d)\n", c, auxID);
            if( garageList->first->ID == auxID ) {
                if( !insertAtRear(roadList, garageList -> first) )
                    printf("error");

                if( !deleteByID(garageList, auxID) )
                    printf("error");
            }
            else {
                printf("error:_%d_not_at_exit!\n", auxID);
            }
        }

        else if(c == 'S'){  /// show trucks
            char c2 = fgetc(filePtr);
            printf("%c(%c)\n", c, c2);
            if(c2 == 'R') {
                printf("R:");
                if(roadList -> count == 0)
                    printf("none\n");
                else {
                    displayID(roadList);
                    printf("\n");
                }
            }
            else if(c2 == 'G') {
                printf("G:");
                if(garageList -> count == 0)
                    printf("none\n");
                else {
                    displayID(garageList);
                    printf("\n");
                }
            }
            else {
                printf("error! impossible command");
            }
        }

        else {
            printf("error! impossible command");
            exit(1);
        }

        fgetc(filePtr);    /// to pass ')'
        fgetc(filePtr);    /// to pass '\n'
    }
    return 0;
}
