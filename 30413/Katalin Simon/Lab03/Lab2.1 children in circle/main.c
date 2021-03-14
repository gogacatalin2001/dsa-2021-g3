#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//DLL node structure
typedef struct node_type
{
  char* word; //words
  int count;//monitoring duplicate words
  struct node_type *next; /* pointer to next node */
  struct node_type *prev; /* pointer to previous node */
} NodeT;

// Example of doubly-linked list header cell type definition
typedef struct
{
  //int count; /* number of elements in this list; an optional field */
  NodeT *first; /* link to the first node in the list */
  NodeT *last; /* link to the last node in the list */
} DLListT;

int isEmpty(DLListT *listPtr)
{
    if(listPtr->first == NULL && listPtr->last == NULL) return 1;
    return 0;
}

// Sample code to create an empty singly-linked list-->same in case of DLL
/* Create an empty list */
DLListT *createEmptyDLL()
{
  DLListT *listPtr = (DLListT*)malloc(sizeof(DLListT));
  if (listPtr)
  {
    //listPtr->count = 0; // list empty
    listPtr->first = listPtr->last = NULL;
  }
  return listPtr;
}

// Example code to create and fill a DLL node with data
/* Create a node and fill it with data */
NodeT *createDLLNode(char *key)
{
   NodeT *p = (NodeT *)malloc(sizeof(NodeT));
   if (p)
   {
      // what is done here depends on the data stored at the node
      strcpy(p->word,key);
      p->count=1;
      p->next = p->prev = NULL; // initialize links for disconnected node */
   }
   //if not using strcasecmp then change uppercase chars to lowercase
   return p;
}
//----- Listing.3.17 --- Code part 17 ----------------------
// Example code traversing a DLL
void tranverseForw(DLListT *listPtr, NodeT *p)
// traverse DLL in forward direction
{
    if(!isEmpty(listPtr)) {
        for ( p = listPtr->first; p!= NULL; p = p->next )
        {
          printf("%s:%d\n", p->word, p->count);

        }
    }
    else printf("Empty list\n");
}
/**int tranverseForwSearch(DLListT *listPtr, NodeT *p, char *newStr)
///traverse DLL in forward direction
{
    NodeT *q;
    if(!isEmpty(listPtr)) {
        for ( p = listPtr->first; p!= NULL; p = p->next )
        {
            if(p==listPtr->first && (strcmp(p->word,newStr)==-1 || strcmp(p->word,newStr)==0))
            {
                //insert node
                q=createDLLNode(newStr);
                insertAtFront(listPtr,q);
                return 1;

            }
            else
            if(p==listPtr->last && (strcmp(p->word,newStr)==1 || strcmp(p->word,newStr)==0))
            {
                q=createDLLNode(newStr);
                insertAtRear(listPtr,q);
                return 1;
            }
            else
            if((strcmp(p->word,newStr)==-1 || strcmp(p->word,newStr)==0) && (strcmp(p->next->word,newStr)==1 || strcmp(p->next->word,newStr)==0))
            {
                q=createDLLNode(newStr);
                //insertAtRear(listPtr,q);
                //insert ater p
                q->prev=p;
                q->next=p->next;
                p->next->prev=q;
                p->next=q;
                //inserted q
                return 1;
            }
            printf("%s\n", p->word);
        }
    }
    else printf("Empty list\n");
    return 0;
}*/
NodeT *find(DLListT *listPtr, char* givenKey)//needs adjustments for sorting
{
   NodeT *p;
   p = listPtr->first;
   while ( p != NULL )
     if ((strcasecmp(p->word,givenKey)<0) &&(strcasecmp(p->next->word,givenKey)>0)) // Note. This comparison does work for primitive types only
     {
        return p; //key found in cell p
     }
     else if(strcasecmp(p->word,givenKey)==0) {p->count++; exit(11);}
     else if(strcasecmp(p->next->word,givenKey)==0) {p->next->count++; exit(11);}
     else
        p = p->next;
   return NULL; // not found
}
int tranverseForwSearch(DLListT *listPtr, char *newStr)
///traverse DLL in forward direction
{
    NodeT *q = createDLLNode(newStr);
    if (strcasecmp(listPtr->first->word,newStr)>0)
    {
        insertAtFrontBeforeOther(listPtr,q);
    }
    else if (strcasecmp(listPtr->first->word,newStr)==0)
    {
        listPtr->first->count++;
    }
    else if (strcasecmp(listPtr->last->word,newStr)<0)
    {
        insertAtRearAfterOther(listPtr,q);
    }
    else if (strcasecmp(listPtr->last->word,newStr)==0)
    {
        listPtr->last->count++;
    }
    else
    {//we need to insert somewhere in the list-->look for pos
    //use function for this then insert it
    //our list should be ordered!

    if(find(listPtr,newStr))
        {
            insertToList(point, point->next,newStr);
        }
    }
}

void tranverseBackw(DLListT *listPtr,  NodeT *p)
// traverse DLL in backward direction
{

    if(!isEmpty(listPtr)) {
        for ( p = listPtr->last; p!= NULL; p = p->prev )
        {
          printf("%s:%d\n", p->word, p->count);

        }
    }
    else printf("Empty list\n");
}

//----- Listing.3.19 --- Code part 19 ----------------------
// Example code for inserting a node at the beginning or end of a DLL
// Example code for insertAtFront; does not check for duplicate keys
int insertAtFront(DLListT *listPtr, NodeT *p)
{
  if (listPtr)
  { // the list is non null
     if (isEmpty(listPtr))
     {
        // p will be the sole node in the list
        listPtr->first = listPtr->last = p;
        p->prev = p->next = NULL; // p is the first and single node
     }
     else
     {
        p->next = listPtr->first; // chain before the former first node
        listPtr->first= p; // p is before the former first node
        p->prev = NULL; // p is the first node
     }
     //listPtr->count++;
     return 1; // success
   }
   return 0; // failure
}
// Example code for insertAtRear; does not check for duplicate keys
int insertAtRear(DLListT *listPtr, NodeT *p)
{
  if (listPtr)
  {  // the list is non null
     if (isEmpty(listPtr))
     {
        // p will be the sole node in the list
        listPtr->first = listPtr->last = p;
        p->prev = p->next = NULL; // p is the first and single node
     }
     else
     { // non-empty list
        listPtr->last->next = p; // chain after the former last node
        p->prev = listPtr->last; // p is after the former last node
        p->next = NULL; // p is the last node
        listPtr->last = p;
     }
     //listPtr->count++; // increment number of nodes
     return 1; // success
  }
  return 0; // failure
}
int insertAtFrontBeforeOther(DLListT *listPtr, NodeT *p)
{
    listPtr->first->prev = p;
    p->next = listPtr->first; // chain with former first
    listPtr->first = p;
    return 0; // failure
}
// Example code for insertAtRear; does not check for duplicate keys
int insertAtRearAfterOther(DLListT *listPtr, NodeT *p)
{
    listPtr->last->next = p; // chain after the former last node
    p->prev = listPtr->last; // p is after the former last node
    listPtr->last = p;
    return 0; // failure
}
//----- Listing.3.20 --- Code part 20 ----------------------
// Sample code for searching a node with a given key in a DLL, preceeding an insert operation
 /**   NodeT *q;
    q = listPtr->first;
    while ( q != NULL )
    {
       if ( q->word == givenKey ) break;
       q = q->next;
    }*/
//----- Listing.3.21 --- Code part 21 ----------------------
// Sample code for inserting a node with a given key in a DLL
/**    if ( q != NULL )
    {  // node with key givenKey has address q
       if ( q == listPtr->first )
       {  // insert before first node
          p->next = listPtr->first; // chain with former first
          listPtr->first = p; // set p as first node
          p->prev = NULL;
       }
       else
       {
          q1->next = p;
          p->prev = q1;
          p->next = q;
          q->prev = p;
       }
       listPtr->count++; // increment number of nodes
       // success
    }*/
    // failure;

// Sample code for inserting a node with a given key in a DLL
 /**   if ( q != NULL )
    {  // node with key givenKey has address q
       p->next = q->next;
       q->next->prev = p;
       q->next = p;
       p->prev = q;
       if ( q == listPtr->last ) listPtr->last = p;
       listPtr->count++; // increment number of nodes
       //success
    }*/
  // failure
//----- Listing.3.23 --- Code part 23 ----------------------
// Purging a DLL
/**NodeT *p;

while ( listPtr->first != NULL )
{
  p = listPtr->first;
  listPtr->first = listPtr->first->next;
  free( p );
}
listPtr->last = NULL;*/
//-----  --- Code part 24 ----------------------
// Purging a DLL \begin{lstlisting}{}
typedef struct circularList
{
  int length;
  NodeT *first, *current;
} CircularSLLT;

void purge (DLListT *listPtr)
{
    NodeT *p;
    while(listPtr->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        free(p);
    }
    listPtr->last=NULL;
}//i might use it

void insertToList (NodeT *word1, NodeT *word2, NodeT *wordNew)
{
    word1->next = wordNew;
    word2->prev = wordNew;
    wordNew->next = word2;
    wordNew->prev = word1;
}//when we obtain the exact position a node/word should be entered

//int main()
int main(int argc, char **argv)//*argv==*argv
{
    FILE *input;
    FILE *output;

    DLListT *listPtr=createEmptyDLL();
    NodeT *p, *q;//for creating and working with nodes

    //char  *argv[3];//main on pos 0, input on pos 1, output file name on pos 2-- used for testing
    //*(argv+1)="in.txt"; argv[2]="out.txt";
    if(argc==1)
    {
        printf("Please provide the command line arguments");
        return 0;
    }
    //fcanf instead of fget c... it war nearly impossible to work with chars
    //char ch;//character by character
    input=fopen(argv[1], "r");
    output=fopen(argv[2], "w");

    //we should read the first word
    char words[100];//assume words won't be longer than 100 characters
    fscanf(input, "%s", words);
    p=createDLLNode(words);

    ///in order to link our list to the node
    listPtr->first=p;
    listPtr->last=p;

    //now we may read the other words
    while (fscanf(input,"%s",words) != EOF)
    {
        //here first of all we scould look for inserting it into the list in the correct order
        //if we find it in the list, then we increment our count
        tranverseForwSearch(listPtr,words);
        //should do all the work
    }

    //display info//do i have to set listPtr?
    tranverseForw(listPtr,p);
    printf("\n");
    tranverseBackw(listPtr,p);
   //closing the I/O files
   purge(listPtr);
   fclose(input);
   fclose(output);
    return 0;
}
//git is not working
