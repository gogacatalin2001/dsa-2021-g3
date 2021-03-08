#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int key; /* an optional field identifying the data */
  /* other useful data fields */
  struct node *next; /* link to next node */
} NodeT;

typedef struct
{
  int count; /* an optional field */
  NodeT *first; /* link to the first node in the list */
  NodeT *last; /* link to the last node in the list */
} ListT;

ListT *createEmptySLL()
{
	ListT *listPtr = (ListT*)malloc(sizeof(ListT));
	if (listPtr)
	{
		listPtr->count = 0; // list empty
		listPtr->first = listPtr->last = NULL;
	}
	return listPtr;
}

NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        // what is done here depends on the data stored at the node
        p->key = key; // assignment allowed as the key is of a primitive type
        p->next = NULL;
    }
    return p;
}

int countLines(FILE *filePtr)   /// returns number of lines in file pointed to by filePtr
{
    int lines = 0;
    for(;;) {
        char c = fgetc(filePtr);
        if(c == EOF) {
            lines++;
            break;
        }
        else if (c == '\n') {
            lines++;
        }
    }
    rewind(filePtr);
    return lines;
}

int isEmpty(ListT *listPtr)
{
    if(listPtr -> count == 0 && listPtr -> first == NULL && listPtr -> last == NULL) {
        return 1;
    }
    return 0;
}

int insertAtRear(ListT *listPtr, NodeT *p)
{
	if (listPtr)
	{  // the list is non null
		if (isEmpty(listPtr))
		{  // p will be the sole node in the list
			listPtr->first = p;
		}
		else
		{ // non-empty list
			listPtr->last->next = p;
		}
		listPtr->last = p;
		listPtr->count++; // increment number of nodes
		return 1; // success
	}
	return 0; // failure
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        p->next = listPtr->first;
        if (isEmpty(listPtr))
        {
            // p will be the sole node in the list
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure
}

NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if ( listPtr->first != NULL )
    {
        // non-empty list
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        // free( p ); // free up memory
        listPtr->count--; // decrease the number of nodes
        if ( listPtr->first == NULL ) // list is now empty
            listPtr->last = NULL;
        return p;
    }
    return NULL;
}

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

void displayID(ListT *listPtr, FILE *fileO)
{
    NodeT *t = listPtr->first;
    int i;
    for (i = 0; i < listPtr->count; i++) {
        fprintf(fileO, "_%d", t->key);
        t = t->next;
    }
    fprintf(fileO, "\n");
}

int main(int argc, char *argv[])
{
    FILE *filePtr = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    int i, auxID;
    int numberLines = countLines(filePtr);

    ListT *roadList = createEmptySLL();
    ListT *garageList = createEmptySLL();

    for(i = 0; i < numberLines; i++)    /// for every line i read the command and then the truck ID = auxID
    {                                   /// or 'G'/'R' when c == 'S'
        char c = fgetc(filePtr);
        fgetc(filePtr); /// to pass '('

        if(c == 'R'){
        /// place truck on road:
        /// create truck with ID auxID
        /// add that truck at the rear of roadList
            fscanf(filePtr, "%d", &auxID);
            //printf("%c(%d)\n", c, auxID);
            if( !insertAtRear(roadList, createSLLNode(auxID)) )
                fprintf(fileO, "error\n");
        }

        else if(c == 'E'){
        /// truck enters the garage:
        /// check if the truck with ID auxID is the first from roadList
            /// if not display error:_auxID_not_first_on_road!
            /// if yes add that truck in front of garageList, delete that truck from roadList
            fscanf(filePtr, "%d", &auxID);
            //printf("%c(%d)\n", c, auxID);
            if(roadList->first->key == auxID) {
                NodeT * auxT = deleteFirst(roadList);
                if( !insertAtFront(garageList, auxT ))
                    fprintf(fileO, "error\n");
            }
            else {
                if(find(roadList, auxID) == NULL)
                    fprintf(fileO, "error:_%d_not_on_road!\n", auxID);
                else
                    fprintf(fileO, "error:_%d_not_first_on_road!\n", auxID);
            }
        }

        else if(c == 'X'){
            /// truck exits the garage:
            /// check if truck with auxID is the first of garageList
                /// if yes, add that truck at rear of roadList, remove truck from the front of garageList
                /// if not, display error:_auxID_not_at_exit!
            fscanf(filePtr, "%d", &auxID);
            //printf("%c(%d)\n", c, auxID);
            if(garageList->first->key == auxID) {
                    NodeT *auxT2 = deleteFirst(garageList);
                if( !insertAtRear(roadList, auxT2) ) {
                    fprintf(fileO, "error\n");
                }
            }
            else {
                fprintf(fileO, "error:_%d_not_at_exit\n", auxID);
            }
        }

        else if(c == 'S'){  /// show trucks
            char c2 = fgetc(filePtr);
            //printf("%c(%c)\n", c, c2);
            if(c2 == 'R') {
                fprintf(fileO, "R:");
                if(roadList -> count == 0)
                    fprintf(fileO, "none\n");
                else {
                    displayID(roadList, fileO);
                }
            }
            else if(c2 == 'G') {
                fprintf(fileO, "G:");
                if(garageList -> count == 0)
                    fprintf(fileO, "none\n");
                else {
                    displayID(garageList, fileO);
                }
            }
            else {
                fprintf(fileO, "error! impossible command");
            }
        }

        else {
            fprintf(fileO, "error! impossible command");
            exit(1);
        }

        fgetc(filePtr);    /// to pass ')'
        fgetc(filePtr);    /// to pass '\n'
    }
    return 0;
}
