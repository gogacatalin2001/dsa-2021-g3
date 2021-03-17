#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
  int key; /* an optional field identifying the data */
  /* other useful data fields */
  struct node *next; /* link to next node */
} NodeT;

typedef struct
{
  int count; /* an optional field */
  NodeT *first; /* link to the first node in the list */
  NodeT *last; /* link to the last node in the list */
} ListT;

ListT *RList;
ListT *GList;

ListT *createEmptySLL()
{
	ListT *listPtr = (ListT*)malloc(sizeof(ListT));
	if (listPtr)
	{
		listPtr->count = 0; // list empty
		listPtr->first = listPtr->last = NULL;
	}
	return listPtr;
}
int isEmpty(ListT *listPtr)
{
    if(listPtr->count == 0)
        return 1;
    else
        return 0;
}
NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        // what is done here depends on the data stored at the node
        p->key = key; // assignment allowed as the key is of a primitive type
        p->next = NULL;
    }
    return p;
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        p->next = listPtr->first;
        if (isEmpty(listPtr))
        {
            // p will be the sole node in the list
            listPtr->last = p;
        }

        listPtr->first = p;
        listPtr->count++;

        return 1; // success
    }
    return 0; // failure
}
int insertAtRear(ListT *listPtr, NodeT *p)
{
	if (listPtr)
	{  // the list is non null
		if (isEmpty(listPtr))
		{  // p will be the sole node in the list
			listPtr->first = p;
		}
		else
		{ // non-empty list
			listPtr->last->next = p;
		}
		listPtr->last = p;
		listPtr->count++; // increment number of nodes
		return 1; // success
	}
	return 0; // failure
}



NodeT *find(ListT *listPtr, int givenKey)
{
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
        if ( p->key == givenKey ) /* Note. This comparison does work for primitive types only */
        {
            return p; /* key found in cell p */
        }
        else
            p = p->next;
    return NULL; /* not found */
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
        listPtr->count--; // decrease the number of nodes
        if ( listPtr->first == NULL ) // list is now empty
            listPtr->last = NULL;
        return p;
    }
    return NULL;
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
	{   /* found a node with supplied key */
	  if ( q == listPtr->first )
	  { /* is the first node */
	    listPtr->first = listPtr->first->next;
	    free( q ); /* release memory */
	    if ( listPtr->first == NULL ) listPtr->last = NULL;
	  }
	  else
	  { /* other than first node */
	    q1->next = q->next;
	    if ( q == listPtr->last ) listPtr->last = q1;
	    free( q ); /* release memory */
	  }
	  return 1; // success
	}
	return 0; // failure
}

void R(unsigned int truck_id)
{
    /// add to the Road List
    if (!insertAtRear(RList, createSLLNode(truck_id)))
        printf("error"),exit(0);
}
void E(unsigned int truck_id, char *argv)
{
     FILE *g = fopen(argv, "a");
    /// i insert it only if i find it on the road so first :
    if(find(RList, truck_id)!=NULL)
    {
        if (!insertAtRear(GList, createSLLNode(truck_id)))
            fprintf(g,"error insert rear"),exit(0);
        ///remove from road
        deleteByKey(RList, truck_id);
    }
    else fprintf(g,"error: %d not on road!\n", truck_id);
fclose(g);
}
void X(unsigned int truck_id, char *argv)
{
    FILE *g = fopen(argv, "a");
    ///delete truck from garage list
    if (GList->first->key == truck_id)
    {
        deleteFirst(GList);

         /// add truck to road
        if(!insertAtRear(RList, createSLLNode(truck_id)))
            fprintf(g,"error insert Rear"), exit(0);
    }
    else
        fprintf(g,"error: %d not at exit!\n", truck_id);
fclose(g);

}
void S(char c, char *argv)
{
    FILE *g = fopen(argv, "a");
    if(c == 'R')
    {
        ///print the RList
        if (RList->count == 0)
        {
            fprintf(g,"R: none\n");
            return;
        }
        NodeT *q;
        q = RList->first;

        fprintf(g,"R:");
        while ( q != NULL )
        {
            fprintf(g," %d", q->key);
            q = q->next;
        }
        fprintf(g,"\n");
    }
    else if ( c == 'G')
    {
        /// print the GList
        if (GList->count == 0)
        {
            fprintf(g,"G: none\n");
            return;
        }
        NodeT *q;
        q = GList->first;

        fprintf(g,"G:");
        while ( q != NULL )
        {
            fprintf(g," %d", q->key);
            q = q->next;
        }
        fprintf(g,"\n");
    }
    else {
        printf("There is no such option for S");
    }
    fclose(g);
}

int main(int argc, char *argv[])
{

    RList = createEmptySLL();
    GList = createEmptySLL();

    FILE *f = fopen(argv[1], "r");

    size_t linesz = 20;
    char *line = malloc(linesz *sizeof(char));
    if(!line)
    {
        printf("error alocating memory");
        exit(0);
    }

    while (fgets(line, linesz, f))
    {
        switch(line[0])
        {
            case 'R':
            {
                int i = 2;
                int numb = 0;
                if(isdigit(line[i]))
                {
                    //numb = line[i] - '0';
                    while(line[i]!=')')
                    {
                        numb = numb*10 + (line[i] - '0');
                        i++;
                    }
                    unsigned int truck_id = numb;
                   // printf()
                    R(truck_id);
                }
                else printf("error at R read");
;
                break;
            }
            case 'E':
            {
                int i = 2;
                int numb = 0;

                if(isdigit(line[i]))
                {
                    //numb = line[i] - '0';
                    while(line[i]!=')')
                    {
                        numb = numb*10 + (line[i] - '0');
                        i++;
                    }
                    unsigned int truck_id = numb;
                    E(truck_id,argv[2]);
                }
                else printf("error at E read");
                break;
            }
            case 'X':
            {
                int i = 2;
                int numb = 0;

                if(isdigit(line[i]))
                {
                    //numb = line[i] - '0';
                    while(line[i]!=')')
                    {
                        numb = numb*10 + (line[i] - '0');
                        i++;
                    }
                    unsigned int truck_id = numb;
                    X(truck_id,argv[2]);
                }
                else printf("error at X read");
                break;
            }
            case 'S':
            {

                S(line[2],argv[2]);
                break;
            }
        }
    }

    fclose(f);

    return 0;
}
