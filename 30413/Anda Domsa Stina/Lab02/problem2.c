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
int enqeueRoad(Road *listPtr, truck *p)
{
	if (listPtr)
	{  // the list is non null
		if (listPtr->count==0)
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
int enqeueGarage(Garage *listPtr, truck *p)
{
	if (listPtr)
	{  // the list is non null
		if (listPtr->count==0)
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
truck *deqeueRoad(Road *listPtr)
{
    truck *p;
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
truck *deqeueGarage(Garage *listPtr)
{
    truck *p;
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
int R(Road *listPtr, int nr)
{
    enqeueRoad(listPtr,nr);
}
int E(int nr, Road *listPtr, Garage *listG)
{
    if(listPtr->first==nr)
    {
        deqeueRoad(listPtr);
        enqeueGarage(listG, nr);
    }
    else
    {
        printf("truck %d not at front", nr);
    }

}
int X(int nr, Road *listPtr, Garage *listG)
{

    if(nr==listG->first)
    {
         deqeueGarage(listG );
         enqeueRoad(listPtr, nr);
    }
   else
   {
       printf("truck %d not at exit!", nr);
   }

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
    //if R -> insertAtRear in Road;
    //if E -> insertAtRear in garage and delete the first in Road if nr=id;
    //if X -> delete first in garage and insertAtRear in Road;
    //if S(G) output of garage, S(R) output of road
    //int nr;

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
}
