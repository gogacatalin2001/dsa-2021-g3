#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    char key[20];
    int apar; //count the apparitions of the key
    struct node_type *next; /* pointer to next node */
    struct node_type *prev; /* pointer to previous node */
} NodeT;

typedef struct
{
    int count; /* number of elements in this list; an optional field */
    NodeT *first; /* link to the first node in the list */
    NodeT *last; /* link to the last node in the list */
} ListT;

ListT *createEmptyDLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0; // list empty
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createDLLNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        // what is done here depends on the data stored at the node
        strcpy(p->key,key); // assignment allowed as the key is of a primitive type
        p->next = p->prev = NULL; // initialize links for disconnected node */
        p->apar=0;
    }
    return p;
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        if (listPtr->count==0)
        {
            // p will be the sole node in the list
            listPtr->first = listPtr->last = p;
            p->prev = p->next = NULL; // p is the first and single node
        }
        else
        {
            p->next = listPtr->first; // chain before the former first node
            listPtr->first->prev = p; // p is before the former first node
            p->prev = NULL; // p is the first node
            listPtr->first=p;
        }
        listPtr->count++;
        p->apar++;
        return 1; // success
    }
    return 0; // failure
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        if (listPtr->count==0)
        {
            // p will be the sole node in the list
            listPtr->first = listPtr->last = p;
            p->prev = p->next = NULL; // p is the first and single node
        }
        else
        {
            // non-empty list
            listPtr->last->next = p; // chain after the former last node
            p->prev = listPtr->last; // p is after the former last node
            p->next = NULL; // p is the last node
            listPtr->last=p;
        }
        listPtr->count++;
        p->apar++; // increment number of nodes
        return 1; // success
    }
    return 0; // failure
}


NodeT *search_by_key(ListT *listPtr, char *givenKey)
{
    NodeT *q;
    q = listPtr->first;
    while ( q != NULL )
    {
        if ( strcmp(q->key,givenKey)==0 ) return q;
        q = q->next;
    }
    return 0;
}


void add_after_key(ListT *listPtr, char *givenKey, NodeT *p)
{
    NodeT *q;
    q = listPtr->first;
    while (q!=NULL)
    {
        if ( strcmp(q->key,givenKey)==0) break;
        q = q->next;
    }
    if ( q != NULL )
    {
        /* node with key givenKey has address q */
        p->next = q->next;
        q->next->prev = p;
        q->next = p;
        p->prev = q;
        if ( q == listPtr->last ) listPtr->last = p;
        listPtr->count++; // increment number of nodes
        p->apar++; //increment nr of aparitions

    }


}


int main(int argc, char **argv)
{
    ListT *lista;
    FILE *fr=fopen(argv[1],"r");
    FILE *pw=fopen(argv[2],"w");
    lista=createEmptyDLL();

    if(lista==NULL) printf("Error! List could not be allocated!");

    char b;
    int words=1;
    b=fgetc(fr);
    while(b!=EOF)
    {
        if((b==' ') || (b==NULL)) words++; //count number of words
        b=fgetc(fr);
    }
    rewind(fr);

    int i;
    char cuv[20];
    NodeT *find_node,*p,*t;

    for(i=0; i<words; i++)
    {
        fscanf(fr,"%s ",cuv);
        find_node=search_by_key(lista,cuv);

        if(lista->count==0)
        {
             p=createDLLNode(cuv);
             insertAtFront(lista,p);
        }

        if(find_node==0)
        {
            p=createDLLNode(cuv);
            if(strcasecmp(lista->first->key,cuv)>0) ///key is smaller than any other keys in the list
                insertAtFront(lista,p);

            else if(strcasecmp(lista->last->key,cuv)<0) ///key is greater than any other key in the list
                insertAtRear(lista,p);

            else            ///key must be inserted between 2 existing nodes
            {
                for ( t = lista->first; t != NULL; t = t->next )
                {

                    if(strcasecmp(t->key,cuv)<0 && strcasecmp(t->next->key,cuv)>0)
                    {
                        add_after_key(lista,t->key,p);
                        break;
                    }

                    else if(strcasecmp(t->key,cuv)==0 && strcmp(t->key,cuv)!=0)
                    {
                        add_after_key(lista,t->key,p);
                        break;
                    }
                }
            }

        }
        else find_node->apar++;

    }
    p=lista->first;

    while(p!=NULL)
    {
        fprintf(pw,"%s:%d\n",p->key,p->apar);
        p=p->next;
    }
    fprintf(pw,"------------------------------------\n");
    p=lista->last;

    while(p!=NULL)
    {
        fprintf(pw,"%s:%d\n",p->key,p->apar);
        p=p->prev;
    }



    return 0;
}
