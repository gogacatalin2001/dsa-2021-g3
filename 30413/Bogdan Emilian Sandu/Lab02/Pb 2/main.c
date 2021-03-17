#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
int truck_id;
bool on_road;
struct node *next;
} NodeT;

typedef struct List {
NodeT *first, *last;
}ListT;

ListT* CreateList() //creaza lista goala
{
    ListT *listPtr=(ListT*)malloc(sizeof(ListT));
    listPtr->first=listPtr->last=NULL;
    return listPtr;
}
NodeT* CreateNode(int id)
{
    NodeT *nodePtr=(NodeT*)malloc(sizeof(NodeT));
    if(nodePtr!=NULL)
    {nodePtr->truck_id=id;
    nodePtr->on_road=true;
    nodePtr->next=NULL;}
    else exit(1);
    return nodePtr;
}
NodeT *find(ListT *listPtr, int givenKey)
{
   NodeT *p;
   p=listPtr->first;
   while(p!=NULL)
   {
       if(p->truck_id == givenKey) return p;
    else p=p->next;
   }
   return NULL;
}
void InsertNode(ListT *listPtr, NodeT *p) //at front; can also be used to insert in stack/garage
{
    p->next=listPtr->first;
    if(listPtr->first==NULL && listPtr->last==NULL)
        listPtr->last=p;
    listPtr->first=p;
}
bool verifGarage(NodeT *p, ListT *garagePtr)
{
    if(garagePtr->first==p) return true;
    else return false;
}

NodeT *deleteGarage(int truck_id, ListT *garagePtr, char argv[])
{
    NodeT *p=find(garagePtr, truck_id);
    if(verifGarage(p, garagePtr)==true)
    {
        if(garagePtr->first != NULL)
        {
            p=garagePtr->first;
            garagePtr->first=garagePtr->first->next;
            if(garagePtr->first == NULL)
                garagePtr->last=NULL;
            return p;
        }
    }
        FILE *out=fopen(argv,"a");
        fprintf(out," %d not at entrance of garage or not in garage\n",truck_id);
        fclose(out);
        return NULL;
}
NodeT* deleteByKey(ListT *listPtr, int givenKey)
{
    NodeT *q, *q1;
    q1=NULL;
    q=listPtr->first;
    while(q!=NULL)
    {
        if(q->truck_id==givenKey) break;
        q1=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        if(q == listPtr->first)
           {
           listPtr->first=listPtr->first->next;
           if(listPtr->first==NULL) listPtr->last=NULL;
           }
           else {
            q1->next=q->next;
            if(q==listPtr->last) listPtr->last=q1;
           }
    }
    return q;
}//era int initial
void insertOnRoad(int id, ListT *listPtr) //functia R, care acm e circular drumul
{
    NodeT *p=CreateNode(id);
    InsertNode(listPtr,p);
    listPtr->last->next=listPtr->first;
}
void insertOnRoadG(int id,ListT *listPtr, ListT *garagePtr, char argv[]) //functia X, sterge din garaj si baga pe drum,
{
    NodeT *p=deleteGarage(id, garagePtr,argv);
    if(p!=NULL) InsertNode(listPtr, p);
    else return;
    p->on_road=true;
    listPtr->last->next=listPtr->first;
}
void insertInGarage(ListT *garagePtr, ListT *listPtr, int id, char argv[]) //functia E
{
    if(listPtr->last->truck_id==id)
    {NodeT *p=deleteByKey(listPtr,id);
    InsertNode(garagePtr,p);
    p->on_road=false;
    listPtr->last->next=listPtr->first;
    }
    else {
        FILE *out=fopen(argv,"a");
        fprintf(out," error %d not at front of queue or not on road\n", id);
        fclose(out);
    }
}
void showLists(char c, ListT *listPtr, ListT *garagePtr,char argv[]) //functia S
{
    if(c=='G')
    {
        FILE *out=fopen(argv,"a");
        NodeT *curr1=garagePtr->first;
        if(curr1==NULL) {
            fprintf(out," none\n");
            fclose(out);
            return;
        }
        while(curr1!=NULL)
        {
           if(curr1->on_road==false) fprintf(out," %d",curr1->truck_id);
           curr1=curr1->next;
        }
        fprintf(out,"\n");
        fclose(out);
    }
    else if(c=='R')
    {
        FILE *out=fopen(argv,"a");
        NodeT *curr2=listPtr->first;
        if(curr2==NULL)
        {
           fprintf(out," none\n");
            fclose(out);
           return;
        }
        do
        {
            if(curr2->on_road==true) fprintf(out," %d",curr2->truck_id);
            curr2=curr2->next;
        }while(curr2!=listPtr->first);
        fprintf(out,"\n");
        fclose(out);
    }
}
void purge(ListT *listPtr)
{
    NodeT *p;
    while (listPtr->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        free(p);
    }
    listPtr->last=NULL;
}
void purgeR(ListT *listPtr)//purge la lista circulara
{
NodeT *p;
while(listPtr->last->next!=listPtr->first)
{
    p=listPtr->first;
    listPtr->first = listPtr->first->next;
    free(p);
}
p=listPtr->first;
listPtr->last = NULL;
listPtr->first=NULL;
free(p);
}
int main(int argc, char* argv[])
{
    FILE *p, *out;
    ListT *listPtr, *garagePtr;
    listPtr=CreateList();
    garagePtr=CreateList();
    p=fopen(argv[1],"r");
    out=fopen(argv[2],"w");
    char c,s,str[50];
    int d;
    while((c=getc(p))!=EOF)
          {
              switch(c)
                {
                case 'R':
                    if (fscanf(p,"(%d)",&d)==1){
                    getc(p);
                    insertOnRoad(d,listPtr);}
                    else exit(1);
                    break;
                case 'E':
                    if(fscanf(p,"(%d)",&d)==1){
                    getc(p);
                    insertInGarage(garagePtr,listPtr,d,argv[2]);}
                    else exit(1);
                    break;
                case 'X':
                    if(fscanf(p,"(%d)",&d)==1){
                    getc(p);
                    insertOnRoadG(d,listPtr,garagePtr,argv[2]);}
                    else exit(1);
                    break;
                case 'S':
                    if(fscanf(p,"(%c)",&s)==1){
                    getc(p);
                    showLists(s,listPtr,garagePtr,argv[2]);}
                    else exit(1);
                    break;
                default:
                    fgets(str,50,p);
                    out=fopen(argv[2],"a");
                    fprintf(out," error, unknown command\n");
                    fclose(out);
                }
          }
    fclose(p);
    fclose(out);
    purge(garagePtr);
    purgeR(listPtr);
    free(listPtr);
    free(garagePtr);
    return 0;
}
