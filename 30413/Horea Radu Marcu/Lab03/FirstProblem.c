#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define NOT_FOUND -1
typedef struct
{
    char name[22];
    int next;
}NodeT;

typedef struct
{
    unsigned int capacity;
    int available;
    int first;
    int count;
    NodeT *data;
}ArrListT;

ArrListT *createCSLL(int size)
{
    ArrListT *listPtr = (ArrListT*)malloc(sizeof(ArrListT));
    if(listPtr)
    {
        listPtr->data=(NodeT*)malloc(size*sizeof(NodeT));
        if(listPtr->data)
        {
            listPtr->capacity=size;
            listPtr->first=-1;
            listPtr->count=0;
            listPtr->available=0;
            int i=0;
            for(i=0;i<listPtr->capacity-1;i++) listPtr->data[i].next=i+1;
            listPtr->data[listPtr->capacity-1].next=NOT_FOUND;
        }
        else
        {
            free(listPtr);
            listPtr=NULL;
        }
    }
    return listPtr;
}

static int next(ArrListT *listPtr, int current)
{
    return listPtr->data[current].next;
}
int insert(ArrListT *listPtr, char *cuv)
{
    if(listPtr->available==NOT_FOUND) return NOT_FOUND;
    strcpy(listPtr->data[listPtr->available].name, cuv);
    int last=listPtr->first;
    if(last==NOT_FOUND)
    {
        listPtr->first=listPtr->available;
        listPtr->available=next(listPtr, listPtr->available);
    }
    else
    {
        int k=0;
        while(k!=listPtr->count) last=next(listPtr,last),k++;
        int aux = next(listPtr, listPtr->available);
        listPtr->data[listPtr->available].next=listPtr->first;
        listPtr->data[last].next=listPtr->available;
        listPtr->available=aux;
    }
    listPtr->count++;
    return listPtr->first;
}
int main(int argc, char *argv[])
{
    FILE *f=fopen(argv[1], "r");
    int n;
    fscanf(f,"%d", &n);
    ArrListT *children=createCSLL(n);
    int i=0;
    char *nume=(char*)malloc(22*sizeof(char));
    for(i=0;i<n;i++)
    {
        fscanf(f,"%s", nume);
        insert(children, nume);
    }

    int k=0, currentIndex=0, previousIndex=0;
    while(children->count!=1)
    {
        currentIndex++;
        previousIndex=currentIndex-1;
        if(currentIndex>children->count)
        {
            previousIndex=children->count-1;
            currentIndex=0;
        }
        k++;
        if(k==n)
        {
            children->data[previousIndex].next= children->data[currentIndex].next;
            children->data[currentIndex].next=children->available;
            children->available=currentIndex;
            children->first=previousIndex;
            children->count--;
            k=0;
        }
    }
    FILE *g=fopen(argv[2], "w");
    fprintf(g,"%s", children->data[0].name);
    return 0;
}
