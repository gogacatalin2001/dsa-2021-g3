//----- Listing.3.1 --- Code part 01 ----------------------
// Sample singly-linked list node type definition
typedef struct node
{
  int key; /* an optional field identifying the data */
  /* other useful data fields */
  struct node *next; /* link to next node */
} NodeT;
/////----- Listing.3.2 --- Code part 02 ----------------------
///// Sample singly-linked list node type definition for array-based implementation
///typedef struct node
///{
///  int key; /* an optional field identifying the data */
///  /* other useful data fields */
///  int next; /* index of the next node */
///} NodeT;
//----- Listing.3.3 --- Code part 03 ----------------------
// Circular singly-linked list header cell structure when an array-based implementation is used.
///typedef struct node
///{
///   unsigned int capacity; // the maximum number iof elements this list is able to store
///   int available; // index of the next available (unused) location of the data area
///   int first; // index of the first element
///   int count; // the number of elements currently stored in the list; optional
///   NodeT *data; // pointer to array holding the elements
///} ArrListT;
//----- Listing.3.4 --- Code part 04 ----------------------
// Sample list creation for array-based implementation
// create a (circular) singly-linked list by allocating space to store its elements
ArrListT *createCSLL(int size)
{
  ArrListT *listPtr = (ArrListT *) malloc(sizeof(ArrListT));
  if (listPtr)
    {   // have header cell; allocate data area
    listPtr->data = (NodeT *) calloc(size, sizeof(NodeT));
    if (listPtr->data)
    {
      listPtr->capacity = size;
      listPtr->first = -1;
      listPtr->count = 0;
      listPtr->available = 0; // all the data area is available
      // link all the available storage into the available list
      // i.e chain to the next element
      for (int i = 0; i < listPtr->capacity - 1; i++)
      {
        listPtr->data[i].next = i + 1;
      }
      // mark end of available memory
      listPtr->data[listPtr->capacity - 1].next = NOT_FOUND;
    }
    else
    {
      free(listPtr);
      listPtr = NULL;
    }
  }
  return listPtr;
}
//----- Listing.3.5 --- Code part 05 ----------------------
// Finding a n node with a given key for array-based implementation.
#define NOT_FOUND -1
// returns the index of the next node in list pointed to by listPtr
static int next(ArrListT *listPtr, int current)///why is that static?
{
  return listPtr->data[current].next; // specific implementation
}
// returns the index of the node with key key in in list pointed to by listPtr
// or NOT_FOUND if key key is not found
int find(ArrListT *listPtr, int key)
{
  if (isEmpty(listPtr))
    return NOT_FOUND; // -1 is used for non-existing indexes
  int current = listPtr->first;
  do
  {  // scan the list
    if (listPtr->data[current].key == key)
      return current; // found
    current = next(listPtr, current);
  }
  while (current != listPtr->first); // till we come back where we started
  return NOT_FOUND;
}
//----- Listing.3.6 --- Code part 06 ----------------------
// Inserting a node at the front or end of a list for array-based implementation.
// Insert a node with key key in in list pointed to by listPtr.
int insert(ArrListT *listPtr, int key)
{
  if (listPtr->available == NOT_FOUND)
     return NOT_FOUND; // list is full
  // copy the data payload to store at the node in the first available cell
  listPtr->data[listPtr->available].key = key;
  int last = listPtr->first;
  // check if the list is not empty
  if (last == NOT_FOUND)
  {
    listPtr->first = listPtr->available;
    listPtr->available = next(listPtr->available);
  }
  else
  {
     while (next(listPtr, last) != listPtr->first)
     {   // scan the list for the last element
       last = next(listPtr, last);
     }

     int aux = next(listPtr, listPtr->available); // save chaining in available list
     listPtr->data[listPtr->available].next = listPtr->first; // make list circular with new element
     // chain the last element to the new one
     listPtr->data[last].next = listPtr->available;
     listPtr->available = aux; // change beginning of available slots
  }
  listPtr->count++; // cell added
  return listPtr->first;
}
//----- Listing.3.7 --- Code part 07 ----------------------
// Finding a n node with a given key for array-based implementation.
// copy the data in the first location available in the backing storage, temporary
if (listPtr->available != NOT_FOUND)
{ // there is available storage for new elements
  // the next statement assumes that only the key is stored in every node
  listPtr->data[listPtr->available].key = givenKey;
}
else
{ // TODO: print a warning message and quit; no more space in the list
  // other approaches exist, although
}
int currentIndex, prevIndex;

prevIndex = -1; /* initialize as out of the list */
currentIndex = listPtr->first;
do
{
  prevIndex = currentIndex;
  currentIndex = next(listPtr, currentIndex);
  if ( listPtr->data[currentIndex].key == givenKey ) break;
}
while ( currentIndex != listPtr->first );
// now current either holds the index of the node with the given key
// or not
//----- Listing.3.8 --- Code part 08 ----------------------
// Chaining a node for array-based implementation when inserting a node before one with a given key.
if ( listPtr->data[currentIndex].key == givenKey )
{ /* node with key givenKey has index currentIndex */
  listPtr->data[prevIndex].next = listPtr->available;
  listPtr->data[listPtr->available].next = currentIndex;
  // adjust available memory
  listPtr->available = next(listPtr, listPtr->available);
}
// else given key not found; no changes to the list needed
//----- Listing.3.9 --- Code part 09 ----------------------
// Finding a n node with a given key for array-based implementation.
// copy the data in the first location available in the backing storage, temporary
if (listPtr->available != NOT_FOUND)
{ // there is available storage for new elements
  // the next statement assumes that only the key is stored in every node
  listPtr->data[listPtr->available].key = givenKey;
}
else
{ // TODO: print a warning message and quit; no more space in the list
  // other approaches exist, although
}
int currentIndex = listPtr->first;
do
{
  currentIndex = next(listPtr, currentIndex);
  if ( listPtr->data[currentIndex].key == givenKey ) break;
}
while ( currentIndex != listPtr->first );
// now current either holds the index of the node with the given key
// or not
//----- Listing.3.10 --- Code part 10 ----------------------
// Chaining a node for array-based implementation for insertion after a node with a given key.
if ( listPtr->data[currentIndex].key == givenKey )
{ /* node with key givenKey has index currentIndex */
  listPtr->data[listPtr->available].next = listPtr->data[currentIndex].next;
  listPtr->data[currentIndex].next = listPtr->available;
  // adjust available memory
  listPtr->available = next(listPtr, listPtr->available);
}
// else given key not found; no changes to the list needed
//----- Listing.3.11 --- Code part 11 ----------------------
// Deleting a node for array-based implementation when deleting a nodewith a given key.
if ( listPtr->data[currentIndex].key == givenKey )
{ /* node with key givenKey has index currentIndex */
  // skip node with key
  listPtr->data[prevIndex].next = listPtr->data[currentIndex].next;
  // add node to the front of available list
  listPtr->data[currentIndex].next = listPtr->available;
  listPtr->available = currentIndex;
  // set previous node as first node
  listPtr->first =prevIndex;
  listPtr->count--;
  if (listPtr->count == 0)
    purge(listPtr);
}
// else given key not found; no changes to the list needed
//----- Listing.3.12 --- Code part 12 ----------------------
// Purging a CSLL
// purge the list. I.e. simply initialize it again.
void purge(ArrListT *listPtr)
{
   listPtr->first = -1;
   listPtr->count = 0;
   listPtr->available = 0; // all the data area is available
   // link all the available storage into the available list
   // i.e chain to the next element
   for (int i = 0; i < listPtr->capacity - 1; i++)
   {
      listPtr->data[i].next = i + 1;
   }
   // mark end of available memory
   listPtr->data[listPtr->capacity - 1].next = NOT_FOUND;
}
//----- Listing.3.13 --- Code part 13 ----------------------
// Example DLL node structure
typedef struct node_type
{
  int key; /* we assume here that the data is an integer key alone */
  // a more general implementation would include a statement like the following
  DataT data; /* useful data payload; may contain a field used as a key */
  struct node_type *next; /* pointer to next node */
  struct node_type *prev; /* pointer to previous node */
} NodeT;
//----- Listing.3.14 --- Code part 14 ----------------------
// Example of doubly-linked list header cell type definition
typedef struct
{
  int count; /* number of elements in this list; an optional field */
  NodeT *first; /* link to the first node in the list */
  NodeT *last; /* link to the last node in the list */
} DLListT;
//----- Listing.3.15 --- Code part 15 ----------------------
// Sample code to create an empty singly-linked list
/* Create an empty list */
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
//----- Listing.3.16 --- Code part 16 ----------------------
// Example code to create and fill a DLL node with data
/* Create a node and fill it with data */
NodeT *createDLLNode(int key)
{
   NodeT *p = (NodeT *)malloc(sizeof(NodeT));
   if (p)
   {
      // what is done here depends on the data stored at the node
      p->key = key; // assignment allowed as the key is of a primitive type
      p->next = p->prev = NULL; // initialize links for disconnected node */
   }
   return p;
}
//----- Listing.3.17 --- Code part 17 ----------------------
// Example code traversing a DLL
// traverse DLL in forward direction
for ( p = listPtr->first; p != NULL; p = p->next )
{
  /* some operation o current cell */
}
// traverse DLL in backward direction
for ( p = listPtr->last; p != NULL; p->p->prev )
{
  /* some operation o current cell */
}
//----- Listing.3.18 --- Code part 18 ----------------------
// Example code for a function to find a node with a given key in a DLL
NodeT *find(ListT *listPtr, int givenKey)
{
   NodeT *p;
   p = listPtr->first;
   while ( p != NULL )
     if ( p->key == givenKey ) /* Note. This comparison does work for primitive types only */
     {
        return p; /* key found in cell p */
     }
     else
        p = p->next;
   return NULL; /* not found */
}
//----- Listing.3.19 --- Code part 19 ----------------------
// Example code for inserting a node at the beginning or end of a DLL
// Example code for insertAtFront; does not check for duplicate keys
int insertAtFront(ListT *listPtr, NodeT *p)
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
        listPtr->first->prev = p; // p is before the former first node
        p->prev = NULL; // p is the first node
     }
     listPtr->count++;
     return 1; // success
   }
   return 0; // failure
}
// Example code for insertAtRear; does not check for duplicate keys
int insertAtRear(ListT *listPtr, NodeT *p)
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
     }
     listPtr->count++; // increment number of nodes
     return 1; // success
  }
  return 0; // failure
}
//----- Listing.3.20 --- Code part 20 ----------------------
// Sample code for searching a node with a given key in a DLL, preceeding an insert operation
    NodeT *q;
    q = listPtr->first;
    while ( q != NULL )
    {
       if ( q->key == givenKey ) break;
       q = q->next;
    }
//----- Listing.3.21 --- Code part 21 ----------------------
// Sample code for inserting a node with a given key in a DLL
    if ( q != NULL )
    {  /* node with key givenKey has address q */
       if ( q == listPtr->first )
       {  /* insert before first node */
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
    }
    // failure;
//----- Listing.3.22 --- Code part 22 ----------------------
// Sample code for inserting a node with a given key in a DLL
    if ( q != NULL )
    {  /* node with key givenKey has address q */
       p->next = q->next;
       q->next->prev = p;
       q->next = p;
       p->prev = q;
       if ( q == listPtr->last ) listPtr->last = p;
       listPtr->count++; // increment number of nodes
       //success
    }
  // failure
//----- Listing.3.23 --- Code part 23 ----------------------
// Purging a DLL
NodeT *p;

while ( listPtr->first != NULL )
{
  p = listPtr->first;
  listPtr->first = listPtr->first->next;
  free( p );
}
listPtr->last = NULL;
//-----  --- Code part 24 ----------------------
// Purging a DLL \begin{lstlisting}{}
typedef struct circularList
{
  int length;
  NodeT *first, *current;
} CircularSLLT;

int main()
{

    return 0;
}
