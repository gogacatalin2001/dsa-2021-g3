///Words are read from a file whose name is a given as a command line argument. The output should also be sent
///to a file whose name is a command line argument. Words are sequences containing only letters, and separated by
///whitespace. You should insert all the unique words in a doubly-linked list, sorted in ascending order of the words.
///The list should contain in its data cells every distinct word and its number of occurrences in the input file. The
///output should be the content of the list in ascending and descending order, as shown in the example below. .
///I/O description. Input: a single line of text. (But, note: it may be quite long.) See the example below:



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
typedef struct nodty
{
int nr;
char c[100];
struct nodty *next;
struct nodty *prev;
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

NodeT *createDLLNode(char *c)
{
NodeT *p = (NodeT*)malloc(sizeof(NodeT));
if(p)
{
strcpy(p->c,c);
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
        if(strcmp(p->c, givenWord)==0)
        {
        p->nr++;
        return p;
        }
        else p = p->next;
    }
    return NULL;
}


int main(int argc, char *argv[])
{
FILE *f = fopen(argv[1],'r');
printf("The argument supplied is %s\n", argv[1]);
if(f==NULL) return 0;
    DLListT *wordsList=createEmptyDLL();
    char c[100];
    while(fscanf(f,"%s", c)==1)
    {
        NodeT *p;
        p=createDLLNode(c);
        if(wordsList->count==0)
        {
            wordsList->first=wordsList->last=p;
            p->prev=p->next=NULL;
            wordsList->count++;
        }
        else if(find(wordsList, c)==NULL)
        {
            NodeT *q;
            q = wordsList->first;
            while(q!=NULL)
            {
                if(strcmp(q->c,c)<0) break;
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
            else if(strcmp(c,wordsList->first->c)<0)
            {
            p->next=wordsList->first;
            wordsList->first->prev=p;
            p->prev=NULL;
            wordsList->first=p;
            wordsList->count++;
            }
        }
    }
    NodeT *p1=wordsList->first;
    NodeT *p2=wordsList->first->next;
for(p1=wordsList->first; p1!=NULL; p1=p1->next)
{
    for(p2=p1->next;p2!=NULL;p2=p2->next)
    {
char firstword[100];
char secondword[100];
strcpy(firstword,p1->c);
strcpy(secondword,p2->c);
firstword[0]=tolower(firstword[0]);
secondword[0]=tolower(secondword[0]);
    if(strcmp(firstword,secondword)>0)
     {
        NodeT *x=createDLLNode(' ');
        strcpy(x->c,p1->c);
        x->nr=p1->nr;
        strcpy(p1->c,p2->c);
        p1->nr=p2->nr;
        strcpy(p2->c,x->c);
        p2->nr=x->nr;
     }
    }
}
NodeT *p=wordsList->first;

        FILE *g=fopen(argv[2], 'w');
        printf("The argument supplied is %s\n", argv[2]);
while(p!=NULL)
{
fprintf(g, "%s:%d\n", p->c, p->nr);
p=p->next;
}

p=wordsList->last;
while(p!=NULL)
{
    fprintf(g, "%s:%d\n", p->c, p->nr);
    p=p->prev;
}


return 0;
}
