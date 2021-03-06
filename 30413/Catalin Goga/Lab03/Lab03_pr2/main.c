#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int apparitions;/// nb of aparitions of the word in the text
    char word[25];
    struct node *next;
    struct node *prev;
}NodeT;

typedef struct
{
    int count;/// nb of nodes in the list
    NodeT *first;/// first node
    NodeT *last;/// last node
}DLListT;

DLListT *createEmptyList()
{
    /// allocating memory for the header
    DLListT *listPtr = (DLListT*)calloc(1,sizeof(DLListT));
    if(listPtr)/// if header is created initialize the values
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createDLLNode(char word[25])
{
    /// allocate memory for the node
    NodeT *p = (NodeT*)calloc(1,sizeof(NodeT));
    if(p)/// if the node is not null assign the word
    {
        strcpy(p->word,word);
        p->apparitions = 1;
        p->prev = p->next = NULL;
    }
    return p;
}

NodeT *findNode(DLListT *listPtr, char word[25])
{
    NodeT *p = listPtr->first;
    while(p != NULL)
    {
        if(strcmp(p->word,word) == 0)
            return p; /// return the node with the given apparitions
        else
            p = p->next;
    }
    return NULL;
}

int insertAtFront(DLListT *listPtr, NodeT *p)
{
    if(listPtr)/// if list exists
    {
        if(listPtr->count == 0)/// if list is empty
        {
            listPtr->first = listPtr->last = p;
            p->next = p->prev = NULL;
        }
        else/// if list is not empty
        {
            listPtr->first->prev = p;
            p->next = listPtr->first;
            p->prev = NULL;
            listPtr->first = p;
        }
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

int insertAtRear(DLListT *listPtr, NodeT *p)
{
    if(listPtr)/// if list exists
    {
        if(listPtr->count == 0)/// if list is mepty
        {
            listPtr->first = listPtr->last = p;
            p->next = p->prev = NULL;
        }
        else/// if list is not empty
        {
            listPtr->last->next = p;
            p->prev = listPtr->last;
            p->next = NULL;
            listPtr->last = p;
        }
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

int insertBefore(DLListT *listPtr,NodeT *p, char word[25])
{
    NodeT *q = listPtr->first;
    if(listPtr)
    {
        while(strcmp(q->word,word) != 0)
        {
            q = q->next;
        }
        if(q == listPtr->first) /// inserting at front
        {
            p->prev = NULL;
            p->next = q;
            q->prev = p;
            listPtr->first = p;
        }
        else
        {
            q->prev->next = p;
            p->prev = q->prev;
            p->next = q;
            listPtr->count++;
        }
        return 1;/// success
    }
    return 0;/// failure
}

int insertAfter(DLListT *listPtr,NodeT *p, char word[25])
{
    NodeT *q = listPtr->first;
    if(listPtr)
    {
        while( (strcmp(q->word,word) != 0) &&(q != NULL) )
        {
            q = q->next;
        }
        if(q == listPtr->last)/// insert at rear
        {
            p->next = NULL;
            p->prev = q;
            q->next = p;
            listPtr->last = p;
        }
        else
        {
            p->next = q->next;
            q->next->prev = p;
            p->prev = q;
            q->next = p;
        }
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

void purge(DLListT *listPtr)
{
    NodeT *p;
    while(listPtr->first != NULL)
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free(p);
    }
    listPtr->last = NULL;
}

void processInput(FILE *in, FILE *out, DLListT *wordList)
{
    char wordBuff[25];/// buffer for reading the words
    NodeT *p,*temp;/// temporary node for list operations

    while(fscanf(in,"%s",wordBuff) != EOF)
    {
        if(wordList->count == 0)/// if the list is empty insert the first word
            insertAtFront(wordList,createDLLNode(wordBuff));

        temp = findNode(wordList,wordBuff);/// search for the node in the list

        if(temp == NULL)
        {
            temp = createDLLNode(wordBuff);
            /// search for the right position
            p = wordList->first;
            while(p != NULL)
            {
                if((strcasecmp(p->word,wordBuff) < 0)
                && (strcasecmp(p->next->word,wordBuff) > 0))
                {
                    insertAfter(wordList,temp,p->word);
                }
                p = p->next;
            }
        }
        else
        {
            temp->apparitions++;
        }
    }
}

void printAscending(FILE *out,DLListT *listPtr)
{
    NodeT *p = listPtr->first;
    while(p != NULL)
    {
        fprintf(out,"%s:%d\n",p->word,p->apparitions);
        p = p->next;
    }
}

void printDescending(FILE *out,DLListT *listPtr)
{
    NodeT *p = listPtr->last;
    while(p != NULL)
    {
        fprintf(out,"%s:%d\n",p->word,p->apparitions);
        p = p->prev;
    }
}

int main(int argc, char **argv)
{
    FILE *in,*out;
    /// open the input and output files
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    /// check for successful open
    if(in == NULL)
    {
        printf("Couldn't open input file!");
        exit(1);
    }
    if(out == NULL)
    {
        printf("Couldn't open output file!");
        exit(1);
    }

    DLListT *wordList = createEmptyList();/// create a list to store the words
    if(wordList)
    {
        processInput(in,out,wordList);
        fprintf(out,"Ascending order: \n");
        printAscending(out,wordList);
        fprintf(out,"\nDescending order: \n");
        printDescending(out,wordList);
    }
    else
    {
        printf("Could not allocate memory for the wordlist!");
        exit(1);
    }

    /// close the files
    fclose(in);
    fclose(out);

    /// free the memory
    purge(wordList);

    return 0;
}
