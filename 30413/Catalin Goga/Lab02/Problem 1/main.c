#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    For this problem we will use the LIFO memory principle for the garage and the FIFO memory principle for the road .
    The problem will be solved using a STACk for storing the trucks in the garage and a QUEUE for storing the trucks on the road.
*/

typedef struct node
{
    int key;
    struct node *next;

} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

ListT *createEmptyList()
{
    ListT *listPtr = (ListT*)calloc(1,sizeof(ListT));/// allocate memory fot the list
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT*)calloc(1,sizeof(NodeT));/// allocate memory for the node
    if(p)
    {
        p->key = key;
        p->next = NULL;
    }
    return p;
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        p->next = listPtr->first;/// list is nonempty
        if(listPtr->count == 0)
        {
            listPtr->last = p;/// list is empty
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

/// insert at the end
int append(ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if(listPtr->count == 0)
        {
            listPtr->first = p;
        }
        else
        {
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

/// insert before a node
int insertBefore(ListT *listPtr, NodeT *p, int givenKeyValue)
{
    NodeT *q;
    q = listPtr->first;/// initialize with the first value of the list
    /// search for the node with the given value
    while(q != NULL)
    {
        if(q->next->key == givenKeyValue)
            break;
        else
            q = q->next;
    }
    /// add thee new pointer before the node with the given value
    if(q)
    {
        if(q == listPtr->first)
        {
            p->next = listPtr->first;
            listPtr->first = p;
        }
        else
        {
            p->next = q->next;
            q->next = p;

        }
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

/// insert after a node
int insertAfter(ListT *listPtr, NodeT *p, int givenKeyValue)
{
    NodeT *q;/// index pointer
    q = listPtr->first;/// initialize with the first value of the list
    /// search for the node with the given value
    while(q != NULL)
    {
        if(q->key == givenKeyValue)
            break;
        else
            q = q->next;
    }
    /// add the new node after the node with the given value
    if(q)
    {
        p->next = q->next;
        q->next = p;
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if(listPtr->first != NULL)
    {
        /// for non-empty list
        p = listPtr->first;
        listPtr->first = p->next;
        //free(p);/// free memory
        listPtr->count--;
        /// for empty list
        if(listPtr->first == NULL)
            listPtr->last = NULL;
        return p;/// return the deleted node
    }
    return NULL;
}

NodeT *deleteLast(ListT *listPtr)
{
    NodeT *p;
    p = listPtr->first;
    if(p)/// list is not empty
    {
        while(p->next != listPtr->last)
            p = p->next;
        if(p == listPtr->first)
        {
            listPtr->first = listPtr->last = NULL;
        }
        else
        {
            listPtr->last = p;
            listPtr->last->next = NULL;
            p = p->next;
            listPtr->count--;
            return p;/// return the deleted node
        }

    }
    /// list is empty
    return NULL;
}

NodeT *deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *p, *q;
    p = NULL;/// pointer for the cell to be deleted
    q = listPtr->first;/// pointer for the cell with key = givenValue
    /// search for the cell with the given value
    while(q->key != givenKey)
    {
        p = q;
        q = q->next;
    }

    if(q)
    {
        /// if the node is the head
        if(q == listPtr->first)
        {
            listPtr->first = q->next;
            listPtr->count--;
            return q;
        }
        /// if the node is th tail
        if( listPtr->first == NULL)
            listPtr->last = NULL;
        /// if the node is not the head neither the tail
        else
        {
            p->next = q->next;
            if(q == listPtr->last)
                listPtr->last = p;
            listPtr->count--;
            return q;
        }
    }
    return NULL;
}

NodeT *findNode(ListT *listPtr, int key)
{
    NodeT *p;
    p = listPtr->first;
    while(p)
    {
        if(p->key == key)
            return p;
        p = p->next;
    }
    return NULL;
}

void purge(ListT *listPtr)
{
    NodeT *p;
    while(listPtr->first != NULL)
    {
        p = listPtr->first;
        listPtr->first = p->next;
        free(p);
    }
    listPtr->last = NULL;
    listPtr->count = 0;
}

void printList(ListT *listPtr)
{
    NodeT *p = listPtr->first;
    while(p)
    {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

/// for STACK

void push(ListT *stackPtr, NodeT *p)
{
   insertAtFront(stackPtr,p);
}

void pop(ListT *stackPtr)
{
  deleteFirst(stackPtr);
}

NodeT *top(ListT *stackPtr)
{
    return stackPtr->first;
}

/// for QUEUE

int enqueue(ListT *queuePtr, NodeT *p)
{
    return append(queuePtr,p);
}

void dequeue(ListT *queuePtr)
{
    deleteFirst(queuePtr);
}

NodeT *front(ListT *queuePtr)
{
    return queuePtr->first;
}

NodeT *rear(ListT *queuePtr)
{
    return queuePtr->last;
}

/// for the problem

void roadError(FILE *out, int key)
{
    fprintf(out,"error: %d not on road!\n",key);
}

void exitError(FILE *out, int key)
{
    fprintf(out,"error: %d not at exit!\n",key);
}

void showTrucks(FILE *out, ListT *listPtr)
{
    NodeT *p;
    p = listPtr->first;
    while(p)
    {
        fprintf(out," %d",p->key);
        p = p->next;
    }
}

int processCommand(FILE *out, ListT *road, ListT *garage, int command, int param, int truck_id)
{
    NodeT *truck = createSLLNode(truck_id);
    switch(command)
    {
        ///command R
        case 1:
            enqueue(road,truck);
            break;
        ///command E
        case 2:
            if(findNode(road,truck_id) != NULL)
            {
                deleteByKey(road,truck_id);
                push(garage,truck);
            }
            else
            {
                roadError(out,truck_id);
                return 0;
            }
            break;
        ///command X
        case 3:
            if(top(garage)->key != truck_id)
            {
                exitError(out,truck_id);
                return 0;
            }
            else
            {
                pop(garage);
                insertAtFront(road,truck);
            }
            break;
        ///command S
        case 4:
            if(param == 0)
            {
                fprintf(out,"G:");
                if(garage->count != 0)
                    showTrucks(out,garage);
                else
                    fprintf(out," none\n");
            }
            if(param == 1)
            {
                fprintf(out,"R:");
                if(road->count != 0)
                    showTrucks(out,road);
                else
                   fprintf(out," none\n");
            }
            break;
    }
    free(truck);
    return 1;
}

void processInput(FILE *in, FILE *out, ListT *road, ListT *garage)
{
    int command = 0, truck_id = 0, param = -1;/// values to pass to processCommand() function
    char cmdBuff[20];/// command buffer
    while(fscanf(in,"%s",cmdBuff))/// reading the input file
    {
        int i = 0;/// index for going trough the command buffer
        /// processing the type of command
        if(cmdBuff[i] == 'R')
            command = 1;
        else if(cmdBuff[i] == 'E')
            command = 2;
        else if(cmdBuff[i] == 'X')
            command = 3;
        else if(cmdBuff[i] == 'S')
            command = 4;

        /// processing the command parameter
        char *paramPtr;
        paramPtr = strtok(cmdBuff,"()");
        paramPtr = strtok(NULL,"()");

        if(*paramPtr == 'G')
            param = 0;
        else if(*paramPtr == 'R')
            param = 1;
        else
            truck_id = atoi(paramPtr);

        /// execute the command
        processCommand(out,road,garage,command,param,truck_id);
    }
}



int main(int argc, char **argv)
{
    ListT *road, *garage;
    road = createEmptyList();/// storing the trucks on the road
    garage = createEmptyList();/// storing the trucks in the garage

    /// opening input file with name given as second argument
    FILE *in = fopen(argv[1], "r");
    if(in == NULL)
    {
        printf("Error opening the input file.");
        exit(1);
    }

    /// opening input file with name given as second argument
    FILE *out = fopen(argv[2], "w");
    if(out == NULL)
    {
        printf("Error opening the output file.");
        exit(1);
    }

    processInput(in,out,road,garage);

    /// close the files
    fclose(in);
    fclose(out);

    /// free the memory
    purge(road);
    purge(garage);

    return 0;
}
