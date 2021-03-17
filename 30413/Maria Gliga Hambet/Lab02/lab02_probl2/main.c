#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int truck_id;
    struct node *next;
} NodeT;

NodeT *newNode (int truck_id)
{
    NodeT *a=(NodeT*)malloc(sizeof(NodeT));
    if(a)
    {
        a->truck_id=truck_id;
        a->next=NULL;
    }
    return a;
}

typedef struct
{
    int nr_total;
    NodeT *first;
    NodeT *last;
} lista;

lista *createEmptyGarage()
{
    lista *ptrGar=(lista*)malloc(sizeof(lista));
    if(ptrGar)
    {
        ptrGar->nr_total=0;
        ptrGar->first= ptrGar ->last=NULL;
    }
    return ptrGar;
}

lista *createEmptyRoad()
{
    lista *ptrRoad=(lista*)malloc(sizeof(lista));
    if(ptrRoad)
    {
        ptrRoad->nr_total=0;
        ptrRoad->first= ptrRoad ->last=NULL;
    }
    return ptrRoad;
}

int insert_elem_front(lista *list_point, NodeT *a)
{
    if(list_point)
    {
        a->next=list_point->first;
        if(list_point->nr_total==0)
            list_point->last=a;
        list_point->first=a;
        list_point->nr_total++;
        return 1;
    }
    return 0;
}
int insert_elem_end(lista *list_point, NodeT*p)
{
    if(list_point)
    {

        if(list_point->nr_total==0)
        {

            list_point->first=p;
        }
        else
        {
            list_point->last->next=p;
        }
        list_point->last=p;
        list_point->nr_total++;
        return 1;
    }
    return 0;
}

int find_elem(lista *list_point, int elem)
{
    NodeT *p;
    p=list_point->first;
    while(p!=NULL)
        if (p->truck_id==elem)
            return 1;
        else p=p->next;
    return 0;

}

int deleteByKey (lista *list_point,int key)
{
    NodeT *q=list_point->first,*q1=NULL;
    while(q!=NULL)
    {

        if (q->truck_id==key) break;
        q1=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        if(q==list_point->first)
        {
            list_point->first=list_point->first->next;
            list_point->nr_total--;
            if(list_point->nr_total==1)
            {
                list_point->last=list_point->first;
                list_point->last->next=NULL;

            }
            if(list_point->first==NULL)
                list_point->last=NULL;
        }
        else
        {
            q1->next=q->next;
            if(q==list_point->last)list_point->last=q1;
            list_point->nr_total--;
        }
        return 1;
    }

    return 0;
}
void R(int truck_id,lista *ptrRoad)
{   ///i create a new node with the given truck id and insert it in the road list
    NodeT *p= newNode(truck_id);
    insert_elem_end(ptrRoad,p);
}
void E(int truck_id,lista *ptrRoad,lista *ptrGar,FILE *fo)
{
    NodeT *p=newNode(truck_id);
    if (find_elem(ptrRoad, truck_id))
    {

        deleteByKey(ptrRoad, truck_id);
        insert_elem_front(ptrGar, p);

    }
    else fprintf(fo,"error: %d not on road\n",truck_id);
}
void X(int truck_id,lista *ptrRoad,lista *ptrGar,FILE *fo)
{   ///the difference from the first problem is here, where we search for the last item in the list (which was
    ///the first one being added)
    if(ptrGar->last->truck_id==truck_id)
    {
        NodeT *p=newNode(truck_id);
        insert_elem_front(ptrRoad,p);
        ///also, here we use deleteByKey, in compr to the first problem where we used deleteFirst
        deleteByKey(ptrGar,truck_id);
    }
    else if(find_elem(ptrGar,truck_id))
        fprintf(fo,"error: %d is not at the exit\n",truck_id);
    else fprintf(fo,"error: %d is not in the garage\n",truck_id);

}
void S(char c,lista *ptrRoad,lista *ptrGar,FILE *fo)
{
    if(c=='G')
    {
        fprintf(fo,"G:");
        if(ptrGar->nr_total==0)
            fprintf(fo," none");
        else
        {
            NodeT *p=ptrGar->first;
            while(p!=NULL)
            {
                fprintf(fo," %d",p->truck_id);
                p=p->next;
            }
        }

    }
    if(c=='R')
    {
        fprintf(fo,"R:");
        if(ptrRoad->nr_total==0)
            fprintf(fo," none");
        else
        {
            NodeT *p=ptrRoad->first;
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
    char c,id[100];
    lista *ptrRoad,*ptrGar;
    FILE *ff=fopen(argv[1],"r");
    FILE *fo=fopen(argv[2],"w");
    ptrGar=createEmptyGarage();
    ptrRoad=createEmptyRoad();


    while(fscanf(ff,"%c(%s)\n",&c,&id)!=EOF)
    {
        if(c=='S')
        {
            S(id[0], ptrRoad, ptrGar,fo);
        }
        else
        {
            int nr=0,i;

            for(i=0; i<strlen(id)-1; i++)
            ///here i substract 1 because the string also read the ")"
            {
                nr=nr*10+id[i]-48;
            }

            switch(c)
            {
            case 'R':
                R(nr,ptrRoad);
                break;
            case 'E':
                E(nr, ptrRoad, ptrGar,fo);
                break;
            case 'X':
                X(nr, ptrRoad, ptrGar,fo);
                break;
            }
        }

    }
    fclose(ff);
    fclose(fo);
    return 0;
}
