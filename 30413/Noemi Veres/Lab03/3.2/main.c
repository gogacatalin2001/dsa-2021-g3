#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>
#include <ctype.h>
/// open a file (if possible)
FILE *openCheck (const char *path, const char *mode, int i)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        puts("cannot open the file");
        exit(i);
    }
    return pf;
}
/// node type
typedef struct node_type
{
    int freq; /*how many times a word appears*/
    char word[30];
    int up;
    struct node_type *next; /* pointer to next node */
    struct node_type *prev; /* pointer to previous node */
} NodeT;
/// header cell
typedef struct
{
    NodeT *first; /* link to the first node in the list */
    NodeT *last; /* link to the last node in the list */
} DLListT;
/// create empty DLL
DLListT *createEmptyDLL()
{
    DLListT *listPtr = (DLListT*)malloc(sizeof(DLListT));
    if (listPtr)
    {
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}
/// create and fill a node
NodeT *createDLLNode(char *word)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        if (isupper(word[0]))
            p->up = 1;
        else  p->up = 0;
        word[0] = tolower(word[0]);
        strcpy (p->word,word);
        p->freq = 1;
        p->next = p->prev = NULL;
    }
    return p;
}
/// insert node between p1 and p
void insert_pos (NodeT *p1, NodeT *p, NodeT *new_node)
{
    p1->next = new_node;
    p->prev = new_node;
    new_node->next = p;
    new_node->prev = p1;
}
/// searching where to insert a node or where to increase the frequency
void find(DLListT *listPtr, char *givenWord)
{
    NodeT *new_node = createDLLNode(givenWord);
    if (strcmp(listPtr->first->word,givenWord)>0)
    {
        /// insert before first node
        listPtr->first->prev = new_node;
        new_node->next = listPtr->first; // chain with former first
        listPtr->first = new_node; // set new_node as first node
    }
    else if (strcmp(listPtr->last->word,givenWord)<0)
    {
        ///at the end
        listPtr->last->next = new_node; // chain after the former last node
        new_node->prev = listPtr->last; // p is after the former last node
        listPtr->last = new_node;
    }
    else
    {
        NodeT *p = listPtr->first, *p1 = NULL;
        while (strcmp(p->word,givenWord) < 0)
        {
            p1 = p;
            p = p->next;
        }
        if (strcmp(p->word,givenWord) == 0)
        {
            ///both uppercase (and no such word with uppercase before) or both lowercase
            if ((p->up == 1 && isupper(givenWord)) || (p->up != 1 && isupper(givenWord) != 1))
            {
                p->freq++;
                free(new_node);
            }
            else if (strcmp(p->next->word,givenWord) == 0)
            {
                ///an uppercase word is already int the list after the lowercase word
                p->next->freq++;
                free(new_node);
            }
            else if (p->up == 1)
            {
                /// p->word is uppercase, the lowercase has to come first
                insert_pos(p1,p,new_node);
            }
            else
            {
                /// p->word is lowercase, given word has to come after
                insert_pos(p,p->next,new_node);
            }
        }
        else
        {
            insert_pos(p1,p,new_node);
        }
    }
}
/// display list
void display (FILE *pOut, DLListT *listPtr, int asc)
{
    NodeT *p;
    if (asc)
        for (p = listPtr->first; p != NULL; p = p->next )
        {
            if (p->up)
                p->word[0] = toupper(p->word[0]);
            fprintf(pOut,"%s:%d\n", p->word, p->freq);
        }
    else // traverse DLL in backward direction
        for (p = listPtr->last; p != NULL; p = p->prev )
        {
            fprintf(pOut,"%s:%d\n", p->word, p->freq);
        }
}
/// Purging a DLL
void purge (DLListT *listPtr)
{
    NodeT *p;
    while ( listPtr->first != NULL )
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free( p );
    }
    listPtr->last = NULL;
}
int main(int argc, char *argv[])
{
    ///open the files
    FILE *pIn = openCheck(argv[1], "r", 1);
    FILE *pOut = openCheck(argv[2], "w", 2);
    ///create empty list
    DLListT *listPtr = createEmptyDLL();
    ///we put the first word in the list
    char wrd[30];
    fscanf(pIn, "%s", wrd);
    NodeT *firstIn = createDLLNode(wrd);
    listPtr->first = firstIn;
    listPtr->last = firstIn;
    ///---------------------------------
    while (fscanf(pIn,"%s",wrd) != EOF)
    {
        find(listPtr,wrd);
    }
    display(pOut,listPtr,1);
    fprintf(pOut,"\n");
    display(pOut,listPtr,0);
    purge(listPtr);
    fclose(pIn);
    fclose(pOut);
    return 0;
}
