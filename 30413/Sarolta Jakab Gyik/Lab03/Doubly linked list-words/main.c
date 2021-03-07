#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_type
{
    char key[15];
    int nr;
    struct node_type *next;
    struct node_type *prev;
} NodeT;
typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;
int isEmpty( ListT *listPtr)
{
    if((listPtr->first == NULL) && (listPtr->last == NULL))
        return 1;
    return 0;
}
ListT *createEmptyDLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}
NodeT *createDLLNode(char *key)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->nr = 1;
        strcpy(p->key, key);
        //printf("%s\n", p->key);
        p->next = p->prev = NULL;
    }
    return p;
}
int findduplicate(ListT *listPtr, char *key)
{
    NodeT *q;
    q = listPtr->first;
    while ( q != NULL )
    {
        if (strcmp(q->key, key) == 0)
        {
            q->nr++;
            return 1;
        }
        q = q->next;
    }
    return 0;
}
NodeT *find(ListT *listPtr, char key[])
{
    NodeT *p;
    p = listPtr->first;
    if((key[0] < 'a' || key[0] > 'z') && (key[0] <'A' || key[0] > 'Z'))
        return NULL;
    int x = strcmpi(p->key, key);
    //printf("x=%d\n", x);
    if(x > 0)
        return NULL;
    while (p != NULL)
    {
        int x = strcmpi(p->key, key);
        //printf("x=%d\n", x);
        NodeT *q;
        if(p->next != NULL)
        {
            q = p->next;
            int y = strcmpi(q->key, key);
            //printf("y=%d\n", y);
            if((x < 0) && (y > 0))
                return p;
            if(!x && (y > 0))
            {
                if(key[0]+32 == p->key)
                    return p;
                else return p->prev;
            }
            p = p->next;
        }
        else return -1;
    }
}
int insertByKey(ListT *listPtr, NodeT *q, NodeT *newNode)
{
    if(q != NULL && q != -1)
    {
        NodeT *p;
        p = q->next;
        newNode->next = p;
        newNode->prev = q;
        p->prev = newNode;
        q->next = newNode;
        listPtr->count++;
        return 1;
    }
    else return 0;
}
int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        if (isEmpty(listPtr))
        {
            listPtr->first = listPtr->last = p;
            p->prev = p->next = NULL;
        }
        else
        {
            p->next = listPtr->first;
            listPtr->first->prev = p;
            p->prev = NULL;
            listPtr->first = p;
        }
        listPtr->count++;
        return 1;
    }
    return 0;
}
int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        if (isEmpty(listPtr))
        {
            listPtr->first = listPtr->last = p;
            p->prev = p->next = NULL;
        }
        else
        {
            p->next = NULL;
            listPtr->last->next = p;
            p->prev = listPtr->last;
            listPtr->last = p;
        }
        listPtr->count++;
        return 1;
    }
    return 0;
}
void traverseForwards(FILE *f, ListT *listPtr)
{
    NodeT *p;
    for(p = listPtr->first; p != NULL; p = p->next)
    {
        fprintf(f, "%s:%d\n", p->key, p->nr);
    }
    fprintf(f, "\n");
}
void traverseBackwards(FILE *f, ListT *listPtr)
{
    NodeT *p;
    for(p = listPtr->last; p!= NULL; p = p->prev)
    {
        fprintf(f, "%s:%d\n", p->key, p->nr);
    }
    fprintf(f, "\n");
}
void purge(ListT *listPtr)
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
int main(int argc, char const **argv)
{
    printf("%d", argc);
    char filename1[10], filename2[10];
    sscanf(argv[1], "%s", &filename1);
    sscanf(argv[2], "%s", &filename2);
    printf("%s\n", filename1);
    printf("%s\n", filename2);
    FILE *f = fopen(filename1, "r");
    FILE *g = fopen(filename2, "w");
    ListT *myList;
    myList = createEmptyDLL();
    char word[15], *x;
    int n;
    while((x = fgetc(f)) != EOF)
    {
        n = 0;
        word[n] = x;
        while(word[n] != ' ')
        {
            x = fgetc(f);
            n++;
            word[n] = x;
        }
        word[++n] = '\0';
        NodeT *newNode;
        newNode = createDLLNode(word);
        if(isEmpty(myList))
        {
            int c = insertAtFront(myList, newNode);
            if(!c)
                printf("Could not insert node\n");
        }
        else
        {
            if(!findduplicate(myList, word))
            {
                NodeT *q;
                q = find(myList, word);
                //printf("q=%s\n", q->key);
                if(q == NULL)
                {
                    int c = insertAtFront(myList, newNode);
                    if(!c)
                        printf("Could not insert node\n");
                }
                else if((q == -1) || (q == myList->last))
                {
                    int c = insertAtRear(myList, newNode);
                    if(!c)
                        printf("Could not insert node\n");
                }
                else
                {
                    int c = insertByKey(myList, q, newNode);
                    if(!c)
                        printf("Could not insert node\n");
                }
            }

        }
        //traverseForwards(g, myList);
        //traverseBackwards(g, myList);
    }
    word[++n] = '\0';
    NodeT *newNode;
    newNode = createDLLNode(word);
    if(isEmpty(myList))
    {
        int c = insertAtFront(myList, newNode);
        if(!c)
            printf("Could not insert node\n");
    }
    else
    {
        if(!findduplicate(myList, word))
        {
            NodeT *q;
            q = find(myList, word);
            if(q == NULL)
            {
                int c = insertAtFront(myList, newNode);
                if(!c)
                    printf("Could not insert node\n");
            }
            else if((q == -1) || (q == myList->last))
            {
                int c = insertAtRear(myList, newNode);
                if(!c)
                    printf("Could not insert node\n");
            }
            else
            {
                int c = insertByKey(myList, q, newNode);
                if(!c)
                    printf("Could not insert node\n");
            }
        }

    }
    traverseForwards(g, myList);
    traverseBackwards(g, myList);
    fclose(f);
    fclose(g);
    purge(myList);
    return 0;
}
