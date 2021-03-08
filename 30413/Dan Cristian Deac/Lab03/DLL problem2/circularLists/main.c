#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///steps solving the problem:
/**
- so i need to store each word in a list
- it appears only once in the list
- counts the number of appearences
- sort the list by dictionary order
- print the list to file in ascending and descending order


[sorting]  : could have an other field which is the possition in the list
    even if the list has its own order.. - too much time, bad code
    - use code to put an element in the list at his place.

*/

///creating the list
typedef struct data_type
{
    int appearances;
    char *word;
} DataT;
typedef struct node_type
{
  //int key; /* we assume here that the data is an integer key alone */
  // a more general implementation would include a statement like the following
  //DataT data; /* useful data payload; may contain a field used as a key */

  int appearances;
  char *data;
  struct node_type *next; /* pointer to next node */
  struct node_type *prev; /* pointer to previous node */
} NodeT;


typedef struct
{
  int count; /* number of elements in this list; an optional field */
  NodeT *first; /* link to the first node in the list */
  NodeT *last; /* link to the last node in the list */
} ListT;

ListT *DLL;

ListT *createEmptyDLL()
{
  ListT *listPtr = (ListT*)malloc(sizeof(ListT));
  if (listPtr)
  {
    listPtr->count = 0; // list empty
    listPtr->first = listPtr->last = NULL;
  }
  return listPtr;
}

NodeT *createDLLNode(char *data) //int key
{printf("flag52");
   NodeT *p = (NodeT *)malloc(sizeof(NodeT));
   printf("flag6");
   if (p)
   {
      p->appearances = 0;printf("flag5");
      strcpy(p->data,data);
      p->next = p->prev = NULL;
   }
   return p;
}
///find word in list
NodeT *find(ListT *listPtr, char *word)//int givenKey
{printf("flag4");
if(listPtr->count == 0) return;
   NodeT *p;

   p = listPtr->first;
   char *res;
   strcpy(res, p->data);
   while ( p != NULL )
     if ( strcmp(res, word) == 0 )
     {
        p->appearances++;
        return p; /* key found in cell p */
     }
     else{
        p = p->next;
        strcpy(res, p->data);
     }

   return NULL; /* not found */
}

int insertAtPlace(ListT *listPtr, NodeT *p) ///modified insertAtRear
{
printf("test");
  if (listPtr)
  {  // the list is non null
     if (listPtr->count == 0)//isEmpty(listPtr)
     {
        listPtr->first = listPtr->last = p;
        printf("flag2");
        p->prev = p->next = NULL; // p is the first and single node
     }
     else
     { // non-empty list
printf("flagNotFrist");


        if (find(listPtr, p->data)==NULL) /// if theres no such word in list
        {
            printf("flag3");
            ///sorting
//            if(strcmp(listPtr->last->data, p->data) == 0)
//            {printf("flag=");
//                ///if they are equal add to back
//                listPtr->last->next = p; // chain after the former last node
//                p->prev = listPtr->last; // p is after the former last node
//                p->next = NULL; // p is the last node
//            }
//            else
            if(strcmp(listPtr->last->data, p->data) < 0)
            {printf("flag<");
                /// add to back when given word is lower in dictionary order
                listPtr->last->next = p; // chain after the former last node
                p->prev = listPtr->last; // p is after the former last node
                p->next = NULL; // p is the last node
                listPtr->last = p;
            }
            else
            {   printf("flag Going to find place to left");
                /// search for its place in the nodes higher then the last
               NodeT *q;
                q = listPtr->last;
                while ( q != NULL )
                {printf("sssss");
                   if (strcmp(q->data, p->data) > 0)
                                break;//q->key == givenKey
                   q = q->prev;
                }
                if(q->prev != NULL)
                    q->prev->next = p;
                p->prev = q->prev;
                if(q->prev != NULL)
                    q->prev = p;
                p->next = q;


               // listPtr->last->next = p; // chain after the former last node
               // p->prev = listPtr->last; // p is after the former last node
               // p->next = NULL; // p is the last node

            }

        }///else increaseAppearance(listPtr, p->data);

     }
     listPtr->count++; // increment number of nodes
     return 1; // success
  }
  return 0; // failure
}

int main()//int argc, char **argv)
{
    DLL = createEmptyDLL();
    printf("flag1");
    insertAtPlace(DLL, createDLLNode("token"));
    printf("flagA");
    insertAtPlace(DLL, createDLLNode("tzoken1"));
    printf("flagB");
    insertAtPlace(DLL, createDLLNode("token"));
    printf("flagC");
    insertAtPlace(DLL, createDLLNode("token2"));
    printf("flagD");

/*
    FILE *f = fopen(argv[1], "r");
    FILE *g = fopen(argv[2], "w");

    size_t linesz = 2000;
    char *line = malloc(linesz *sizeof(char));
    if(!line)
    {
        printf("error alocating memory");
        exit(0);
    }

    fgets(line, linesz, f);
    //fprintf(g,"%s", line);

    char *token = strtok(line, " ");
    while (token != NULL)
    {
        fprintf(g,"%s\n", token);
        if(insertAtPlace(DLL, createDLLNode(token)) == 0)
            printf("failure"),exit(0);
        else printf("success");
        token = strtok(NULL, " ");
    }


    NodeT *q;
    q = DLL->first;
    while ( q != NULL )
    {
       fprintf(g,"%s\n", q->data); //, q->appearances
       q = q->next;
    }*/
    return 0;
}

/*

    DLL = createEmptyDLL();


    FILE *f = fopen(argv[1], "r");


    size_t linesz = 2000;
    char *line = malloc(linesz *sizeof(char));
    if(!line)
    {
        printf("error alocating memory");
        exit(0);
    }

    fgets(line, linesz, f);
*/
/*
void increaseAppeareance(ListT *listPtr, char word[])
{
    NodeT *q;
    q = listPtr->last;
    while ( q != NULL )
    {
        if (strcmp(q->data->word,
                    p->data->word) == 0)
                                break;//q->key == givenKey
                   q = q->prev;
    }
    q->data->appearances++;
}



if(insertAtPlace(DLL, createDLLNode("token"))==0) printf("fail");
    else printf("success");
*/
