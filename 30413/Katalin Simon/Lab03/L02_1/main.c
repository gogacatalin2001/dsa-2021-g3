/**There is a garage where the access road can accommodate any number of trucks at one time. The garage is build
such a way that only the last truck entered can be moved out (that is, a truck cannot overtake another while it is
inside the garage). Each of the trucks is identified by a positive integer (a truck_id). Write a program to handle
truck moves, allowing for the following commands:
a) R(truck_id); // place a truck on the road=create truck truck_id, and put it at the rear of the road
b) E(truck_ id); // selected truck enters in the garage
c) X(truck_id); // selected truck exits the garage
d) S(G or R); // show the trucks in the garage (G) starting with the one closest to entry or on road(R)
If anattempt is made to get out a truck which is not the closest to the garage entry, an error message like the one
shown after the next problem should be issued*/
///remarks
//define road as lifo
//define garage as fifo
#include <stdio.h>
#include <stdlib.h>
#include "functions.c"


typedef struct node///trucks
{
    int key;//for counting the nr of el. in the list(SLL)
    struct node *next;//links to next pointer
}NodeT;//list definition

typedef struct///Garage/Road
{
    int count;//for counting the nr of el. in the list(SLL)
    NodeT *first;//links to next list element
    NodeT *last;///pointer to the last list element
} ListT;


ListT *createEmptySLL()
{
    ListT *listPtr=(ListT*) malloc(sizeof(ListT));//allocating space for our list
    if(listPtr)//not sure
    {
        listPtr->count=0; //list empty
        listPtr->first=listPtr->last=NULL;//describing empty list
        ///not sure if this doess the same as:(but it has to, testing later, wen working with data)
        ///listPtr->first=NULL;
        ///listPtr->last=NULL;
    }
    return listPtr;//return pointer, so we can use it for further operations on our list
}

ListT *createSLLNode(int key)
{
    NodeT *p= (NodeT *)malloc(sizeof(NodeT));//created node
    if(p)
    {
        //operations depending on what is stored in the node
        p->key=key; //assignment allowed as the key is of a primitive type
        p->next=NULL;
    }
    return p;//so that we could work with our node
}

int isEmpty(ListT *listPtr)
{
    if(listPtr->first==NULL && listPtr->last==NULL) return 1;
    return 0;
}

///now describe the operations

int insertAtFront(ListT *listPtr, NodeT *p)///without checking for duplicate keys
{
    if(listPtr)
    {
        //
        p->next=listPtr->first;
        if(isEmpty(listPtr))
        {
            //p the only node of our new list
            listPtr->last=p;
        }
        listPtr->first=p;
        listPtr->count++;
        return 1;//succes
    }
    return 0;//failure, if program returns 0
}

int insertAtRear(ListT *listPtr, NodeT *p)///without checking for duplicate keys
{
    if(listPtr)
    {//the list is non null
        if(isEmpty(listPtr))
        {
            //p the only node of our new list
            listPtr->first=p;
        }
        else
        {//when list is not empty
            listPtr->last->next=p;

        }
        listPtr->last=p;
        listPtr->count++;//i node more-increment
        return 1; //in success

    }
    return 0;//failure
}
/**
insert BEFORE a given node

//searching for a node

//for inside a function or main(also function but a special one, that is why i took it seperately)
NodeT *q, *ql;
ql=NULL;//initialize
q=listPtr->first;
while(q!=NULL)
{
    if(q->key== givenKey) break;
        ql=q;
        q=q->next;
}
*/

//-----------------------------------------

/**

//inserting node with given key

//for inside a function or main(also function but a special one, that is why i took it seperately)
if(q!=NULL)
{//node with given key has addess q
    if(q == listPtr->first);
    {//insert before first node
        p->next=listPtr->first;//chain with former list
        listPtr->first=p;//let p be first node
    }
    else
    {//it has to be inserted inside the list
        ql->next=p;
        p->next=q;
    }
    listPtr->count++;
    //success
}
//failure
*/

//prev two comment sections work when merged, but i separated them for better visualization

/**
insert AFTER a given node

//searching for a node, same as before

//for inside a function or main(also function but a special one, that is why i took it seperately)
NodeT *q, *ql;
ql=NULL;//initialize
q=listPtr->first;
while(q!=NULL)
{
    if(q->key== givenKey) break;
        ql=q;
        q=q->next;
}
*/

//-----------------------------------------

/**

//inserting node with given key

//for inside a function or main(also function but a special one, that is why i took it seperately)
if(q!=NULL)
{
    p->next=q->next;//node with key givenKey has address q
    q->next=p;
    if(q==listPtr->last) listPtr->last=p;
        listPtr_>count++;//more nodes
        //success
}
//failure
*/

NodeT *find(ListT *listPtr, int givenKey)
{
    NodeT *p;
    p=listPtr->first;
    while(p!=NULL)
        if(p->key==givenKey)//comparison, which works only between
        //PRIMITIVE TYPES!
        {
            return p;
        }
        else
            p=p->next;
    return NULL;//node was not found
}///The node to be inserted may be created as shown at§2.3. We will assume here that the node to insert is pointed to by p

NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if(listPtr->first!=NULL)//there are elements in the list
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        //free(p); //free up memory -dynamic memory allocation
        listPtr->count--;//one node less
        if(listPtr->first==NULL)//now our list IS EMPTY
            listPtr->last=NULL;
        return p;
    }
    return NULL;//when not succesful, or when list empty when called
}

NodeT *deleteLast(ListT *listPtr)
{
    NodeT *q, *ql;
    ql=NULL;//initialize
    q=listPtr->first;
    if(q!=NULL)
    {
        //our list is not empty
        while(q!=listPtr->last)
        {
            //advance towards end, while remembering the previous pointer address
            ql=q;
            q=q->next;
        }
        if(q==listPtr->first)
        {
            //1 node
            listPtr->first=listPtr->last=NULL;
        }
        else
        {
            //multiple nodes
            ql->next=NULL;
            listPtr->last=ql;
        }
        //free(q);
    }
    return q;
}

int deleteByKey(ListT *listPtr, int givenKey)// so it can not be the last node??
{
    NodeT *q, *ql;
    ql=NULL;
    q=listPtr->first;
    //search for node now
    while(q!=NULL)
    {
        if(q->key==givenKey) break;
        ql=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        //found the node with the supplied key
        if(q==listPtr->first)
        {//we have to delete forst node
            listPtr->first=listPtr->first->next;
            free(q);//relese memory
            if(listPtr->first==NULL) listPtr->last=NULL;
        }
        else
        {
            //not the first node
            ql->next=q->next;
            if(q==listPtr->last) listPtr->last=ql;
            free(q);//relese memory
        }
        return 1;//on success
    }
    return 0; //on failure
}

/*void purge(ListT *listPtr)
{
    NodeT *p;
    while(p->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        free(p);
    }
    listPtr->last-NULL;
    listPtr->count=0;
}*/

int truckOnRoad(int key, ListT *listPtr, NodeT *p)//does not checks if(there are other trucks on the same road
{
    int *k=find(listPtr,key);
    if(k!=NULL)
    {
        printf("%d truck is already on road(i know this is not needed according to the problem specifications)\n", key);
        return 0;
    }
    else
    {
        //insert at front or rear, it does not matter, since they can overtake each other
        p=createSLLNode(key);///node created seperately
        if(insertAtRear(listPtr,p)==1)
            //showListFrontFirst(listPtr,p);
            return 1;
    return 0;
    }
}
void showListFrontFirst(ListT *listPtr, NodeT *q)//both for road and garage
{
    if(listPtr->count==0) printf("empty\n");
    else
    {
        q=listPtr->first;
        while(q->next!=NULL)
        {
            printf("%d ", q->key);
            q=q->next;
        }
        if(q->next==NULL) printf("%d\n", q->key);
    }
}
int selectedTruckIntoG(int nkey, ListT *listPtrR, NodeT *p, ListT *listPtrG)
///allows to change nodes between lists, insetring it at the front of the other list
{
//    int *k=find(listPtr,nkey);
//    if(listPtrG->first->key!=nkey)
//    {
//        printf("error: %d not at exit!\n", key);
//        return 0;
//    }
//    else
//    {
//        if(insertAtFront(listPtrR,k)==1)
//        {
//
//            deleteByKey(listPtrG,nkey);
//            return 1;
//        }
//        else
//        {
//            printf("error when placing truck to road\n");
//            return 0;
//        }
//    }
///use this at the circular problem
    int *k=find(listPtrR,nkey);
    if(insertAtFront(listPtrG,k)==1)
        {

            deleteByKey(listPtrR,nkey);
            NodeT *a=listPtrG->first;
            showListFrontFirst(listPtrG,a);
            a=listPtrR->first;
            showListFrontFirst(listPtrR,a);
            return 1;
        }
        else
        {
            printf("error when placing truck to road\n");
            return 0;
        }
}
 int selectedTruckToR(int nkey, ListT *listPtrR, NodeT *p, ListT *listPtrG)
///allows to change nodes between lists, insetring it at the front of the other list
{
    //delete truck from garage, adn link it to the front of the road
    if(listPtrG->first->key!=nkey)
    {
        printf("error: %d not at exit!\n", nkey);
        return 0;
    }
    else
    {
        printf("idkerror\n");
        if(insertAtFront(listPtrR,p))
        {

            printf("idkerror\n");
            deleteByKey(listPtrG,nkey);
            NodeT *a=listPtrG->first;
            showListFrontFirst(listPtrG,a);
            showListFrontFirst(listPtrR,a);
            printf("idkerror\n");
            return 1;
        }
        else
        {
            printf("error when placing truck to road\n");
            return 0;
        }
        printf("idkerror\n");
    }

}
//flie beolvasas
int main()
{
    ListT *G=createEmptySLL(), *R=createEmptySLL();//now i have a road and a garage, both empty
    FILE *fpi, *fpo;
    NodeT *q, *ql,*h;
//q=createSLLNode(3);
truckOnRoad(3,R,q);
showListFrontFirst(R,q);

showListFrontFirst(G,q);
printf("\n");
//q=createSLLNode(4);
truckOnRoad(4,R,q);
showListFrontFirst(R,q);
showListFrontFirst(G,q);
printf("\n");

truckOnRoad(34,G,q);
showListFrontFirst(G,q);
showListFrontFirst(R,q);
printf("\n");

selectedTruckToR(34,R,q,G);
showListFrontFirst(G,q);
showListFrontFirst(R,q);
printf("\n");
//q=createSLLNode(5);
truckOnRoad(5,R,q);
showListFrontFirst(G,q);
showListFrontFirst(R,q);
printf("\n");

//q=createSLLNode(6);
truckOnRoad(6,R,q);
showListFrontFirst(G,q);
showListFrontFirst(R,q);
printf("\n");

truckOnRoad(7,R,q);
showListFrontFirst(G,q);
showListFrontFirst(R,q);
printf("\n");

    return 0;
}
