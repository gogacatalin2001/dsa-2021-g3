#include<stdio.h>
#include<stdlib.h>
typedef struct
{
    int id;
    struct truck *next;
} truck;
typedef struct
{
  int count;
  truck *first; /* link to the first node in the list */
  truck *last; /* link to the last node in the list */
} Road;
Road *createEmptySLL()
{
	Road *listPtr = (Road*)malloc(sizeof(Road));
	if (listPtr)
	{
		listPtr->count = 0; // list empty
		listPtr->first = listPtr->last = NULL;
	}
	return listPtr;
}
typedef struct
{
  int count;
  truck *first; /* link to the first node in the list */
  truck *last; /* link to the last node in the list */
} Garage;
Garage *createEmptyS()
{
	Garage *listPtr = (Garage*)malloc(sizeof(Garage));
	if (listPtr)
	{
		listPtr->count = 0; // list empty
		listPtr->first = listPtr->last = NULL;
	}
	return listPtr;
}
int insertAtFrontRoad(Road *listPtr, truck *p)
{
    if (listPtr)
    {
        // the list is non null
        p->next = listPtr->first;
        if (listPtr->count==0)
        {
            //listPtr -> count==0&& listPtr -> first==NULL && listPtr->last==NULL
            // p will be the sole node in the list
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure
}
int Push(Garage *listPtr, truck *p)
{
    if (listPtr)
    {
        // the list is non null
        p->next = listPtr->first;
        if (listPtr->count==0)
        {
            //listPtr -> count==0&& listPtr -> first==NULL && listPtr->last==NULL
            // p will be the sole node in the list
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure
}

int deleteByKey(Road *listPtr, int nr)
{
	truck *q, *q1;
	q1 = NULL; /* initialize */
	q = listPtr->first;
	/* search node */
	while ( q != NULL )
	{
	  if ( q->id == nr ) break;
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
	else
    {
        printf("%d not on road", nr);
    }
	return 0; // failure
}
int Pop(Garage *listG, int nr)
{
     truck *p;
    if ( listG->first != NULL )
    {
        // non-empty list
        p = listG->first;
        listG->first = listG->first->next;
        // free( p ); // free up memory
        listG->count--; // decrease the number of nodes
        if ( listG->first == NULL ) // list is now empty
            listG->last = NULL;
        return p;
    }
    return NULL;
}
int R(Road *listPtr, int nr)
{
    insertAtFrontRoad(listPtr,nr);
}
int E(int nr, Road *listPtr, Garage *listG)
{
    deleteByKey(listPtr, nr);
    Push(listG, nr);
}
int X(int nr, Road *listPtr, Garage *listG)
{
    if(nr==listG->first)
    {
         Pop(listG, nr);
    }
   else
   {
       printf("%d not at exit!", nr);
   }
   insertAtFrontRoad(listPtr, nr);
}
int SG(Garage *listPrl)
{
    truck *p;
    if(listPrl->count==NULL)
    {
        printf("\nthe garage is empty!");
    }
    else
    {
        p=listPrl->count;
        printf("the trucks in the road: ");
        while(p!=NULL)
        {
            printf(" %d",p->id);
            p=p->next;
        }
    }
}
int SR(Road *listPrl)
{
    truck *p;
    if(listPrl->count==NULL)
    {
        printf("\nthe road is empty!");
    }
    else
    {
        p=listPrl->count;
        printf("the trucks on the road: ");
        while(p!=NULL)
        {
            printf(" %d",p->id);
            p=p->next;
        }
    }
}
int main()
{
    FILE *fp;
    char c;
    char fis[ ] = "in.txt";
    fp = fopen(fis, "r");
    Road *listPtr;
    Garage *listG;
    char  ch;
    int nr;
    while(fgetc(ch)!=EOF)
    {
        fgetc(ch);
        if(ch=='R')
        {
            fgetc(ch);
            fscanf("%d",nr);
            fgetc(ch);fgetc(ch);
            R(listPtr,nr);
        }
        else if(ch=='E')
        {
            fgetc(ch);
            fscanf("%d",nr);
            fgetc(ch);fgetc(ch);
            E(nr, listPtr,listG);
        }
         else if(ch=='X')
        {
            fgetc(ch);
            fscanf("%d",nr);
            fgetc(ch);fgetc(ch);
            X(nr,listPtr,listG);
        }
         else if(ch=='S')
        {
            fgetc(ch);
            char v;
            fgetc(v);
            {
                if(v=='R')
                {
                    SR(listPtr);
                }
                else if(v=='G')
                {
                    SG(listG);
                }
            }
            fgetc(ch);
            fgetc(ch);
        }
    }
    return 0;
}
