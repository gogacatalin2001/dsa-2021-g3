#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int count;
    char *word;
    struct Node *next;
    struct Node *prev;
}NodeT;

typedef struct
{
    int k;
    NodeT *first;
    NodeT *last;
}DLL;

NodeT *createNode()
{
    NodeT *Node= (NodeT *)malloc(sizeof(NodeT));
    if(Node)
    {
        Node->count=0;
        Node->word= (char *)malloc(25*sizeof(char));
        Node->next=Node->prev=NULL;
    }
    return Node;
}

DLL *createDLL()
{
    DLL *DLLp= (DLL *)malloc(sizeof(DLL));
    if(DLLp)
    {
        DLLp->k=0;
        NodeT *first= (NodeT *)malloc(sizeof(NodeT));
        NodeT *last= (NodeT *)malloc(sizeof(NodeT));
        if(first && last)
        {
            DLLp->first=first;
            DLLp->last=last;
            first->prev=NULL;
            first->next=last;
            last->prev=first;
            last->next=NULL;
        }
    }
    return DLLp;
}

NodeT *find(DLL *p, char *word)
{
    NodeT *Node= p->first->next;
    while(Node->next!=NULL && strcmp(Node->word, word) <0)
        Node=Node->next;
    return Node;
}

void insert(DLL *p, char *word)
{
    NodeT *findn= find(p,word);
    if(findn!=p->last && strcmp(findn->word,word)==0)
    {
        findn->count++;
    }
        else
            {
                p->k++;
                NodeT *newn= createNode();
                newn->count++;
                strcpy(newn->word,word);
                newn->next=findn;
                newn->prev=findn->prev;
                findn->prev->next=newn;
                findn->prev=newn;
            }
}

void print1(FILE *out, DLL *list)
{
    fprintf(out,"%d",list->k);
    NodeT *node= list->first->next;
    while(node->next!=NULL)
    {
        fprintf(out, "\n%s : %d ",node->word, node->count);
        node=node->next;
    }
}

void print2(FILE *out, DLL *list)
{
    fprintf(out,"\n%d",list->k);
    NodeT *node= list->last->prev;
    while(node->prev!=NULL)
    {
        fprintf(out, "\n%s : %d ",node->word, node->count);
        node=node->prev;
    }
}


int main(int argc,char *argv[])
{
    if (argc != 2) {
    printf("usage: %s, <file_name>", argv[0]);
    return 0;}
    FILE *pf=fopen(argv[1],"r");
    FILE *of=fopen(argv[2],"w");
    if (pf == NULL) printf("can't open file\n");
        else {
               DLL *List= createDLL();
               while(feof(pf)!=NULL)
               {
                   char *word= (char *)malloc(25*sizeof(char));
                   fscanf(pf,"%s",word);
                   insert(List,word);
                   free(word);
               }
               print1(of,List);
               print2(of,List);
             }


    fclose(pf);
    fclose(of);
    return 0;
}
