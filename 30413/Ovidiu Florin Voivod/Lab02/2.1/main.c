#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int key;
    struct node *next;
} NodeT;

typedef struct
{
    int counter; /* an optional field */
    NodeT *first; /* link to the first node in the list */
    NodeT *last; /* link to the last node in the list */
} ListT;

NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->key = key;
        p->next = NULL;
    }
    return p;
}
ListT *createEmptyGarage()
{
    ListT *pGar = (ListT*)malloc(sizeof(ListT));
    if (pGar)
    {
        pGar->counter = 0; // list empty
        pGar->first = pGar->last = NULL;
    }
    return pGar;
}
ListT *createEmptyRoad()
{
    ListT *pRoad = (ListT*)malloc(sizeof(ListT));
    if (pRoad)
    {
        pRoad->counter = 0; // list empty
        pRoad->first = pRoad->last = NULL;
    }
    return pRoad;
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        p->next = listPtr->first;
        if (listPtr->counter==0)
        {
            // p will be the sole node in the list
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->counter++;
        return 1; // success
    }
    return 0; // failure
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {

        if (listPtr->counter==0)
        {

            listPtr->first = p;
        }
        else
        {
            // non-empty list
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->counter++; // increment number of nodes
        return 1; // success
    }
    return 0; // failure
}

NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if ( listPtr->first != NULL )
    {
        // non-empty list
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        // free( p ); // free up memory
        listPtr->counter--; // decrease the number of nodes
        if ( listPtr->first == NULL ) // list is now empty
            listPtr->last = NULL;
        return p;
    }
    return NULL;
}

void deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *q=listPtr->first, *q1=NULL;

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
        if ( q ==listPtr->first )
        {
            /* is the first node */
            listPtr->first = listPtr->first->next;
            listPtr->counter--;
            free( q ); /* release memory */
            if ( listPtr->first == NULL ) listPtr->last = NULL;
        }
        else
        {
            /* other than first node */
            q1->next = q->next;
            if ( q == listPtr->last ) listPtr->last = q1;
            free( q ); /* release memory */
            listPtr->counter--;
        }

    }

}

int find_elem(ListT *listPtr, int nr)
{
    NodeT *p;
    p=listPtr->first;
    while(p!=NULL)
        if (p->key==nr)
            return 1;
        else p=p->next;
    return 0;

}

int charTOint(char *s) //converts truck ID from char to int
{
    int k=0,i;
    for(i=0;i<strlen(s);i++)
    {
        if(strchr("0123456789",s[i])!=NULL)
            k=k*10+s[i]-'0';
    }
    return k;
}

int main(int argc, char **argv)
{

    FILE *fr=fopen(argv[1],"r"); //argv[1] the name of the input file
    FILE *fw=fopen(argv[2],"w"); //argv[2] the name of the output file
    ListT *road, *garage; //declare 2 lists defining the road and the garage
    char string[7];

    road=createEmptyRoad();
    garage=createEmptyGarage();

    //fscanf(fr,"%s",string);
    //printf("%s",string);
    int lines=1;
    char b;

    b=fgetc(fr);
    while(b!=EOF)
    {
        if(b=='\n') lines++; //count the number of commands from the file
        b=fgetc(fr);
    }
    rewind(fr);

    int i;
    for(i=0;i<lines;i++)
    {
        fscanf(fr,"%s",string);
        int nr;
        nr=charTOint(string);

        switch(string[0])
        {
        case 'R':
                insertAtRear(road,createSLLNode(nr));
                break;


        case 'E':
            if(find_elem(road,nr)==1)
            {

                insertAtFront(garage,createSLLNode(nr));
                deleteByKey(road,nr);

            }
            else fprintf(fw,"error: %d not on road\n",nr);
            break;

        case 'X':
            if(garage->first->key==nr)
            {
                NodeT *p=createSLLNode(nr);
                insertAtFront(road,p);
                deleteFirst(garage);
            }
            else if(find_elem(garage,nr)==0) fprintf(fw,"error: %d not in garage!\n",nr);
            else fprintf(fw,"error: %d not at exit!\n",nr);
            break;

        case 'S':
            if(string[2]=='G')
            {
                fprintf(fw,"G: ");
                NodeT *p;
                p=garage->first;
                if(p==NULL) fprintf(fw,"none\n");
                else
                {
                    while(p!=NULL)
                    {
                        fprintf(fw,"%d ",p->key);
                        p=p->next;
                    }
                    fprintf(fw,"\n");
                }


            }
            if(string[2]=='R')
            {
                fprintf(fw,"R: ");
                NodeT *p;
                p=road->first;
                if(p==NULL) fprintf(fw,"none\n");
                else
                {
                    while(p!=NULL)
                    {
                        fprintf(fw,"%d ",p->key);
                        p=p->next;
                    }
                    fprintf(fw,"\n");
                }
            }
            break;




        }
    }
    fclose(fr);
    free(garage);
    free(road);

    return 0;
}
