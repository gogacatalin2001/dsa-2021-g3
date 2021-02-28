#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int truck_id;
    struct node *next;
} NodeT;
NodeT *createNode (int truck_id)
{
    NodeT *t=(NodeT*)malloc(sizeof(NodeT));
    if(t)
    {
        t->truck_id=truck_id;
        t->next=NULL;
    }
    return t;
}
typedef struct
{
    int nr;
    NodeT *first;
    NodeT *last;}ListT;
ListT *createEmptyRoad()
{
    ListT *listPtrRoad = (ListT*)malloc(sizeof(ListT));
    if (listPtrRoad)
      {
        listPtrRoad->nr = 0;
        listPtrRoad->first= listPtrRoad->last= NULL;
    }
    return listPtrRoad;
}
ListT *createEmptyGarage()
{
    ListT *listPtrGarage = (ListT*)malloc(sizeof(ListT));
    if (listPtrGarage)
      {
        listPtrGarage->nr = 0;
        listPtrGarage->first= listPtrGarage->last= NULL;
    }
    return listPtrGarage;
}
//put the truck on the road
int insertFront(ListT *listpt, NodeT *t)
{
    if(listpt)
    {
        t->next=listpt->first;
        if(listpt->nr==0)
            listpt->last=t;
        listpt->first=t;
        listpt->nr++;
        return 1;
    }
    return 0;
}
//put the truck in the garage
int insertRear(ListT *listpt, NodeT*p)
{
    if(listpt)
    {

        if(listpt->nr==0)
        {

            listpt->first=p;
        }
        else
        {
            listpt->last->next=p;
        }
        listpt->last=p;
        listpt->nr++;
        return 1;
    }
    return 0;
}
//search for the truck on the road
int searchElem(ListT *listp, int element)
{
    NodeT *p;
    p=listp->first;
    while(p!=NULL)
        if (p->truck_id==element)
            return 1;//the truck is on the road
        else p=p->next;//keep searching
    return 0;//the truck isn t on the road

}
//now we take out the truck from the road so that we can put it in the garage
//case 1: the chosen truck is at the fron of the list
int DeleteTheFirst(ListT *listp)
{
    if (listp!=NULL)
    {

        listp->first=listp->first->next;
        listp->nr--;
        if(listp->first==NULL)
            listp->last=NULL;
        return 1;
    }
    return 0;
}
//case 2 it s not in the front, we delete it from the given key
int deleteByKey (ListT *listp,int key)
{
    NodeT *q=listp->first,*q1=NULL;
    while(q!=NULL)
    {

        if (q->truck_id==key) break;
        q1=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        if(q==listp->first)
        {
            listp->first=listp->first->next;
            listp->nr--;
            if(listp->first==NULL)
                listp->last=NULL;
        }
        else
        {
            q1->next=q->next;
            if(q==listp->last)listp->last=q1;
            listp->nr--;
        }
        return 1;
    }

    return 0;
}
//now we create the functions R,E,X and S
void R(int truck_id,ListT *listPtrRoad)
{   //create a new node(with the id given) and put it on the road
    NodeT *p= createNode(truck_id);
    insertRear(listPtrRoad,p);
}
void E(int truck_id,ListT *listPtrRoad,ListT *listPtrGarage,FILE *fo)
{
    NodeT *p=createNode(truck_id);
    if (searchElem(listPtrRoad, truck_id))
    {

        deleteByKey(listPtrRoad, truck_id);//it s here, delete it
        insertFront(listPtrGarage, p);

    }
    else fprintf(fo,"error: %d the truck is not on the road\n",truck_id);
}
void X(int truck_id,ListT *listPtrRoad,ListT *listPtrGarage,FILE *fo)
{
    if(listPtrGarage->first->truck_id==truck_id)
    {
        NodeT *p=createNode(truck_id);
        insertFront(listPtrRoad,p);
        DeleteTheFirst(listPtrGarage);
    }
    else if(searchElem(listPtrGarage,truck_id))
        fprintf(fo,"error: %d the truck is not at the exit of the garage\n",truck_id);
    else fprintf(fo,"error: %d the truck is not in the garage\n",truck_id);

}
void S(char word,ListT *listPtrRoad,ListT *listPtrGarage,FILE *fo)
{
    if(word=='G')
    {
        fprintf(fo,"G:");
        if(listPtrRoad->nr==0)
            fprintf(fo," empty");
        else
        {
            NodeT *p=listPtrRoad->first;
            while(p!=NULL)
            {
                fprintf(fo," %d",p->truck_id);
                p=p->next;
            }
        }

    }
    if(word=='R')
    {
        fprintf(fo,"R:");
        if(listPtrRoad->nr==0)
            fprintf(fo," empty");
        else
        {
            NodeT *p=listPtrRoad->first;
            while(p!=NULL)
            {
                fprintf(fo," %d",p->truck_id);
                p=p->next;
            }
        }
    }
    fprintf(fo,"\n");
}
int main(int argc, char **argv)
{
    char word,id[100];
    ListT *listPtrRoad,*listPtrGarage;
    FILE *ff=fopen(argv[1],"r");
    FILE *fo=fopen(argv[2],"w");
    listPtrRoad=createEmptyRoad();
    listPtrGarage=createEmptyGarage();
while(fscanf(ff,"%c(%s)\n",&word,&id)!=EOF)
    {
        if(word=='S')
        {
            S(id[0], listPtrRoad, listPtrGarage,fo);
        }
        else
        {
            int n=0,i;

            for(i=0; i<strlen(id)-1; i++)//minus one because of the ')'
            {
                n=n*10+id[i]-48;
            }

            switch(word)
            {
            case 'R':
                R(n,listPtrRoad);
                break;
            case 'E':
                E(n, listPtrRoad, listPtrGarage,fo);
                break;
            case 'X':
                X(n, listPtrRoad, listPtrGarage,fo);
                break;
            }
        }

    }
    fclose(ff);
    fclose(fo);
    return 0;
}

