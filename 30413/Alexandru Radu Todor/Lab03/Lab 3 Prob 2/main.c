#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node // the node will contain the word from the text and how many times it will appear in the text
{
    char word[50];
    unsigned int occur;
    struct node *prev;
    struct node *next;
}NodeT;

typedef struct // normal list
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

NodeT *createDLLNode(char word[])
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        strcpy(p->word, word);
        p->occur = 1;
        p->next = p->prev = NULL;
    }
    return p;
}

ListT *createEmptyDLL()
{
    ListT *listPtr = (ListT *)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

int insertWord(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        if (listPtr->count == 0) // if the list is empty, the node becomes both the first and last element in it
            listPtr->first = listPtr->last = p;
        else
        {
            NodeT *search = listPtr->first;
            while (stricmp(search->word, p->word) < 0 && search->next != NULL) // we search in the list the first word lexicographically greater or equal than the word we want to introduce (ignoring case sensitive)
                search = search->next;
            if (strcmp(search->word, p->word) == 0) // if the word we found is the same as the one we want to introduce, we increment it's occurrence that is already in the list
            {
                search->occur++;
                listPtr->count--; // at the end of the program we increment the number of items in the list, but since here we don't add anything new, we decrement so it will cancel itself later
            }
            else if (strcmp(search->word, p->word) > 0 && stricmp(search->word, p->word) == 0) // the word we found differs only by case sensitive, and the word we want to add should be after it
            {
                search->next->prev = p;
                p->next = search->next;
                search->next = p;
                p->prev = search;
            }
            else if (search->next == NULL && stricmp(search->word, p->word) < 0) // when no word from the list is bigger than the one we want to add, the word we want to add will be the last
            {
                p->prev = listPtr->last;
                listPtr->last->next = p;
                listPtr->last = p;
            }
            else // since the word we found is the first lexicographically greater than the one we want to add, the word we want to add should be before the one we found
            {
                if (search == listPtr->first) // if the word we found is the first in the list, the word we want to add becomes the first
                    listPtr->first = p;
                else // otherwise, the next after the one before the one we found will be the one we want to add
                {
                    search->prev->next = p;
                    p->prev = search->prev;
                }
                search->prev = p;
                p->next = search;
            }
        }
        listPtr->count++;
        // in the end, we have a list with words in ascending order
        return 1; // success
    }
    return 0; // failed
}

void printList(ListT *listPtr, FILE *out)
{
    int i, j;
    NodeT *p = listPtr->first, *q = listPtr->last;
    // when printing, each line will contain a word and it's complement in the list
    // for example, the complement of the first will be the last, of the second first the second last, an so on
    for (i = 0; i < listPtr->count; i++)
    {
        fprintf(out, "%s:%d", p->word, p->occur); // printing the word
        for (j = 0; j < 55 - strlen(p->word); j++) // how much space should be between words on the line
            fprintf(out, " ");
        fprintf(out, "%s:%d\n", q->word, q->occur); // printing the word's complement
        p = p->next;
        q = q->prev;
    }
}

int main(int argc, char *argv[])
{
    char word[50];
    ListT *listPtr = createEmptyDLL();

    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Input file not found or not introduced!");
        exit(0);
    }
    FILE *out = fopen(argv[2], "w");
    if (out == NULL)
    {
        printf("Output file not introduced!");
        exit(0);
    }

    while (fscanf(in, "%s", word) != EOF)
        insertWord(listPtr, createDLLNode(word));
    printList(listPtr, out);

    fclose(in);
    fclose(out);
    printf("Success!");
    return 0;
}
