#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    int apar;
    struct node *next;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

ListT *CreateEmptySLL()
{
    ListT *listPtr=(ListT*)malloc(sizeof(ListT));
    if(listPtr)
    {
        listPtr->first=listPtr->last=NULL;
        listPtr->count=0;
    }
    return listPtr;

}

NodeT *CreateSLLnode(int key)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->key=key;
        p->next=NULL;
        p->apar=0;
    }
    return p;

}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        if (listPtr->count==0)
        {
            // p will be the sole node in the list
            listPtr->first = p;
        }
        else
        {
            // non-empty list
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++; // increment number of nodes
        return 1; // success
    }
    return 0; // failure
}

int deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *q, *q1;
    q1 = NULL; /* initialize */
    q = listPtr->first;
    /* search node */
    while ( q != NULL )
    {
        if ( q->key == givenKey ) break;
        q1 = q;
        q = q->next;
    }
    if ( q != NULL )
    {
        /* found a node with supplied key */
        if ( q == listPtr->first )
        {
            /* is the first node */
            listPtr->first = listPtr->first->next;
            free( q ); /* release memory */
            if ( listPtr->first == NULL ) listPtr->last = NULL;
        }
        else
        {
            /* other than first node */
            q1->next = q->next;
            if ( q == listPtr->last ) listPtr->last = q1;
            free( q ); /* release memory */
        }
        return 1; // success
    }
    return 0; // failure
}
/**-----------------------------------------------------------**/
/** Function to remove all duplicates from a SLL              **/
/** List will be in ascending order (no restrictions about it)**/
/**-----------------------------------------------------------**/
void RemoveDuplicates(ListT *listPtr)
{
    NodeT *p,*t,*q,*p1;
    int aux,givenKey;
    for(t=listPtr->first; t!=listPtr->last; t=t->next) //sort the keys of the list in ascending order
        for(p=t->next; p!=NULL; p=p->next)
        {
            if(t->key>p->key)
            {
                aux=t->key;
                t->key=p->key;
                p->key=aux;
            }
        }
    p=listPtr->first;
    p1=p->next;

    {
        while(p1!=NULL)
        {
            //p1=p;
           // p=p1->next;
            if(p->key==p1->key)     //search for duplicates
            {

                p->next = p1->next;
                if ( p1 == listPtr->last ) listPtr->last = p;
                //free( p ); /* release memory */
                 //p1=p1->next;

            }
            if(p->key!=p1->key)
            {
                p=p->next;
                p1=p1->next;
            }
            else
            {
                p1=p1->next;
            }

        }
    }


}
/**--------------------------------------------------------------------**/
/** Function to find the intersection node in 2 different lists        **/
/**--------------------------------------------------------------------**/
NodeT *intersection(ListT *listPtr1,ListT *listPtr2)
{
    NodeT *p,*t;
    p=listPtr1->first;
    t=listPtr2->first;
    for(p=listPtr1->first; p!=NULL; p=p->next)
        for(t=listPtr2->first;t!=NULL;t=t->next)
    {
        if(p->key==t->key)
        {
            return p;
            //break;

        }
    }
    return NULL;

}

int main()
{
    char c;
    int x,y;
    ListT *lista,*lista2;
    NodeT *r,*s;
    lista=CreateEmptySLL();
    lista2=CreateEmptySLL();
    printf("Press q to exit adding in the lists:\n");
     NodeT *p;
    citire:


        printf("Write the keys to be added in list 1 and 2/q to exit:");
        scanf("%d%d",&x,&y);
        insertAtRear(lista,(CreateSLLnode(x)));
        insertAtRear(lista2,(CreateSLLnode(y)));
        if(getchar()!='q') goto citire;

    s=intersection(lista,lista2);
    if(s!=NULL) printf("%p %d\n",s,s->key);
    else printf("No intersection! => NULL\n");

    RemoveDuplicates(lista);
    r=lista->first;
    printf("List sorted and without duplicates: ");
    while(r!=NULL)
    {
        printf("%d ",r->key);
        r=r->next;
    }
    return 0;
}
