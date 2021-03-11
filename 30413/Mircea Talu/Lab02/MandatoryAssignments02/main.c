#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int truck_id;
    struct node *next;
}NodeG;

typedef struct
{
    int count;
    NodeG *first;
    NodeG *last;
}ListG;

ListG *createEmptySLL()
{
    ListG *listPtr = (ListG*)malloc(sizeof(ListG));
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

ListG *listPtr;

int Road[100];
int c = 0;

int R(int truck_id)
{
    Road[c] = truck_id;
    c++;
    return 0;
}

int E(int id)
{
    NodeG *p;
    if(listPtr)
    {
        p->next = listPtr->first;
        if(listPtr->count == 0)
            listPtr->last = p;
        listPtr->first = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

int X(int id)
{
    if(listPtr->first->truck_id != id)
    {
        printf("_%d not_at_exit", id);
        return 0;
    }
    else
    {
        R(id);
        listPtr->first = listPtr->first->next;
    }
    return 0;
}

void SR(int A[])
{
    for(int i=0;A[i]!='\0';i++)
        printf("%d_", A[i]);
}

void SG(ListG *G)
{
    if(G->count == 0)
        printf("_none");
    NodeG *p;
    p = listPtr->first;
    while(p != NULL)
    {
        printf("%d ", p->truck_id);
        p = p->next;
    }
    printf("%d ", G->last->truck_id);
}

int main()
{
    FILE *in_file;
    FILE *out_file;
    in_file = fopen("garages.in", "r");
    out_file = fopen("garages.out", "w");
    char line[5];
    int size;
    while (fgets(line, size, in_file))
    {
        switch(line[0])
        {
            case 'R':
            {
                R(line[2]);
            }
            case 'E':
            {
                E(line[2]);
            }
            case 'X':
            {
                X(line[2]);
            }
            case 'S':
            {
                if(line[2] == 'R')
                    SR(Road);
                else
                    SG(ListG *listPtr);
            }
        }
    }
    fclose(in_file);
    fclose(out_file);
    return 0;
}
