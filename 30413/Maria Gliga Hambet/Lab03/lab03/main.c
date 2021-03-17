#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_type
{
  char word[50];
  int nr_aparitii;
  struct node_type *next;
  struct node_type *prev;
} NodeT;

typedef struct
{
  int counter;
  NodeT *first;
  NodeT *last;
} DLListT;

DLListT *createEmptyDLL()
{
  DLListT *listPtr = (DLListT*)malloc(sizeof(DLListT));
  if (listPtr)
  {
    listPtr->counter = 0;
    listPtr->first = listPtr->last = NULL;
  }
  return listPtr;
}

NodeT *createDLLNode(char key[50])
{
   NodeT *p = (NodeT *)malloc(sizeof(NodeT));
   if (p)
   {
      strcpy(p->word,key);
      p->next = p->prev = NULL;
      p->nr_aparitii=1;
   }
   return p;
}

NodeT *find_node(DLListT *listPtr, char givenKey[50])
{
   NodeT *p;
   p = listPtr->first;
   while ( p != NULL )
     if ( strcmp(p->word,givenKey)==0)
     {
        return p;
     }
     else
        p = p->next;
   return NULL;
}
NodeT *find_node_caseins(DLListT *listPtr, char givenKey[50])
{
   NodeT *p;
   p = listPtr->first;
   while ( p != NULL )
     if ( strcasecmp(p->word,givenKey)==0)
     {
        return p;
     }
     else
        p = p->next;
   return NULL;
}
int insertAtFront(DLListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if (listPtr->counter==0)
        {
            listPtr->first = listPtr->last = p;
            p->prev = p->next = NULL;
        }
        else
        {
            p->next = listPtr->first;
            listPtr->first->prev = p;
            p->prev = NULL;
            listPtr->first=p;
        }
        listPtr->counter++;
        return 1;
    }
    return 0;


}

int insertAtRear(DLListT *listPtr, NodeT *p)
{
  if (listPtr)
  {
     if (listPtr->counter==0)
     {

        listPtr->first = listPtr->last = p;
        p->prev = p->next = NULL;
     }
     else
     {
        listPtr->last->next = p;
        p->prev = listPtr->last;
        p->next = NULL;
        listPtr->last=p;
     }
     listPtr->counter++;
    return 1;
  }
return 0;
}

void inserInOrder(char givenKey[50], DLListT *listPtr)
   {
    NodeT *q,*p;
    p=createDLLNode(givenKey);
    q = listPtr->first;
    while ( q != NULL )
    {
       if ( strcasecmp(q->word,givenKey)<0&&strcasecmp(q->next->word,givenKey)>0 )
           break;
       q = q->next;
    }
    if ( q != NULL )
    {
        p->next = q->next;
        q->next->prev = p;
        q->next = p;
        p->prev = q;


    }
    listPtr->counter++;

   }

void adaugare(DLListT *listPtr, char word[50])
{
    NodeT*p=find_node(listPtr,word);
    NodeT*p2=find_node_caseins(listPtr,word);
    NodeT*r=createDLLNode(word);
    if(p!=NULL)
        p->nr_aparitii++;
    else if(p==NULL&&p2!=NULL)
    {
        listPtr->counter++;
        if(strcmp(word,p2->word)<0)
        {
            if(strcmp(listPtr->first,p2->word)==0)
            {
                r->next=listPtr->first;
                listPtr->first->prev=r;
                r->prev=NULL;
                listPtr->first=r;

            }
            else
            {
                r->prev=p2->prev;
                p2->prev->next=r;
                p2->prev=r;
                r->next=p2;
            }


        }
        else
        {   if(strcmp(listPtr->last,p2->word)==0)
            {
                r->prev=listPtr->last;
                listPtr->last->next=r;
                r->next=NULL;
                listPtr->last=r;

            }
            else
            {
                r->next = p2->next;
                p2->next->prev = r;
                p2->next = r;
                r->prev = p2;
            }

        }
    }
    else if (p==NULL&&p2==NULL)
    {

        if(listPtr->counter==0||strcasecmp(word,listPtr->first->word)<0)
                insertAtFront(listPtr,r);


        else if (strcasecmp(word,listPtr->last->word)>0)
            insertAtRear(listPtr,r);

        else
            inserInOrder(word,listPtr);
    }
}

int main(int argc, char **argv)
{
    char c,word[50];
    int contor=0,i;
    DLListT *listPtr=createEmptyDLL();
    FILE* ff=fopen(argv[1],"r");
    FILE* ff2=fopen(argv[1],"r");
    FILE* fo=fopen(argv[2],"w");
    while(fscanf(ff2,"%c",&c)!=EOF)
        if(c==' '||c=='\n')contor++;

    for(i=1;i<=contor+1;i++)
    {
        fscanf(ff,"%s",&word);
        adaugare(listPtr,word);

    }
    NodeT*p=listPtr->first;
    while(p!=NULL)
    {
        fprintf(fo,"%s:%d\n",p->word,p->nr_aparitii);
        p=p->next;
    }
    fprintf(fo,"----------------------\n");
    p=listPtr->last;
    while(p!=NULL)
    {
        fprintf(fo,"%s:%d\n",p->word,p->nr_aparitii);
        p=p->prev;
    }
    return 0;
}
