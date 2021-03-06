#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node_type
{
    int nr;
    char word[22];
    struct node_type *next;
    struct node_type *prev;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}DLListT;

DLListT *createEmptyDLL()
{
    DLListT *listPtr = (DLListT*)malloc(sizeof(DLListT));
    if(listPtr)
    {
        listPtr->count =0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createDLLNode(char *word)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->word,word);
        p->next=p->prev=NULL;
        p->nr=1;
    }
    return p;
}
NodeT *find(DLListT *listPtr, char *givenWord)
{
    NodeT *p;
    p = listPtr->first;
    while(p!=NULL)
    {
        if(strcmp(p->word, givenWord)==0)
        {
            p->nr++;
            return p;
        }
        else p = p->next;
    }
    return NULL;
}
int main(int argc, char **argv)
{
    FILE *f = fopen(argv[1],"r");
    if(f==NULL) return 0;
    DLListT *wordsList=createEmptyDLL();
    char word[22];
    while(fscanf(f,"%s", word)==1)
    {
        NodeT *p;
        p=createDLLNode(word);
        if(wordsList->count==0)
        {
            wordsList->first=wordsList->last=p;
            p->prev=p->next=NULL;
            wordsList->count++;
        }
        else if(find(wordsList, word)==NULL)
        {
            NodeT *q;
            q = wordsList->first;
            while(q!=NULL)
            {
                if(strcmp(q->word,word)<0) break;
                q=q->next;
            }
            if(q!=NULL)
            {
                if(q==wordsList->last)
                {
                    wordsList->last->next=p;
                    p->prev=wordsList->last;
                    p->next=NULL;
                    wordsList->last=p;
                    wordsList->count++;
                }
                else
                {
                    p->next=q->next;
                    q->next->prev=p;
                    q->next=p;
                    p->prev=q;
                    wordsList->count++;
                }
            }
            else if(strcmp(word,wordsList->first->word)<0)
            {
                p->next=wordsList->first;
                wordsList->first->prev=p;
                p->prev=NULL;
                wordsList->first=p;
                wordsList->count++;
            }
        }
    }
    // sortare in ordinea dorita si pentru cuvintele cu litere mari
    NodeT *p1=wordsList->first;
    NodeT *p2=wordsList->first->next;
    for(p1=wordsList->first; p1!=NULL; p1=p1->next)
    {
        for(p2=p1->next;p2!=NULL;p2=p2->next)
        {
            char firstword[22];
            char secondword[22];
            strcpy(firstword,p1->word);
            strcpy(secondword,p2->word);
            firstword[0]=tolower(firstword[0]);
            secondword[0]=tolower(secondword[0]);
           if(strcmp(firstword,secondword)>0)
            {
                NodeT *aux=createDLLNode(" ");
                strcpy(aux->word,p1->word);
                aux->nr=p1->nr;
                strcpy(p1->word,p2->word);
                p1->nr=p2->nr;
                strcpy(p2->word,aux->word);
                p2->nr=aux->nr;
            }
        }
    }
    NodeT *p=wordsList->first;
    FILE *g=fopen(argv[2], "w");
    while(p!=NULL)
    {
        fprintf(g, "%s:%d\n", p->word, p->nr);
        p=p->next;
    }
    p=wordsList->last;
    while(p!=NULL)
    {
        fprintf(g, "%s:%d\n", p->word, p->nr);
        p=p->prev;
    }
    return 0;
}
