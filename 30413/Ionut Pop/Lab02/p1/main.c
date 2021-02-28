#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct node{
    int key;
    struct node *next;
} NodeT;


typedef struct{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

ListT *createEmptySLL(){
    ListT *listPtr=(ListT*) malloc(sizeof(ListT));
    if (listPtr){
        listPtr->count=0;
        listPtr->first=listPtr->last=NULL;
    }
    return listPtr;
}

NodeT *createSLLNode(int key){
    NodeT *p=(NodeT *) malloc(sizeof(NodeT));
    if(p){
        p->key=key;
        p->next=NULL;
    }
    return p;
}


int insertAtFront(ListT *listPtr, NodeT *p){
    if (listPtr){
        p->next=listPtr->first;
        if (isEmpty(listPtr))
            listPtr->last=p;
        listPtr->first=p;
        listPtr->count++;
        return 1;
    }
    return 0;
}


void printList(const ListT *list) {
    NodeT *cpy = list->first;
    while (cpy != NULL) {
        printf("%i ", cpy->key);
        cpy = cpy->next;
    }
    printf("\n");
}

int convertToInt(char *str){
    int nr=0, c=0;
    for (int i=strlen(str)-3;i!=1;--i)
        nr=nr+((str[i]-'0')*pow(10, p++));
}

int deleteByKey(ListT *listPtr, int givenKey){
	NodeT *q, *q1;
	q1 = NULL;
	q = first;
	while ( q != NULL ){
	  if ( q->key == givenKey ) break;
	  q1 = q;
	  q = q->next;
	}
	if ( q != NULL ){
	  if ( q == listPtr->first ){
	    listPtr->first = listPtr->first->next;
	    free( q );
	    if ( listPtr->first == NULL ) listPtr->last = NULL;
	  }
	  else{
	    q1->next = q->next;
	    if ( q == listPtr->last ) listPtr->last = q1;
	    free( q );
	  }
	  return 1;
	}
	return 0;
}

NodeT *deleteLast(ListT *listPtr){
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr->first;
    if ( q != NULL ){
        while ( q != listPtr->last ){
            q1 = q;
            q = q->next;
        }
        if ( q == listPtr->first )
            listPtr->first = listPtr->last = NULL;
        else{
            q1->next = NULL;
            listPtr->last = q1;
        }
    }
    return q;
}

int main()
{
    //first in last out

    FILE *in;
    FILE *out;
    in=fopen("./input.txt", "r");
    out=fopen("./output.txt", "w");

    ListT* garage_list=createEmptySLL();

    char *command = (char *)malloc(100 * sizeof(char));
    while (!feof(in)) {
        fgets(command, 100, in);
        if (command[0]=='S'){
            if (command[2]=='G')
                printList(garage_list);
            else
                printList(garage_list->last);
        }
        else if(command[0]=='X'){
            deleteByKey(convertToInt(command));
        }
        else if(commad[0]=='E'){
            node=createSLLNode(convertToInt(command));
            insertAtFront(garage_list, node);
        }
        else if(commad[0]=='R'){
            deleteLast(garage_list);
        }
    }

    return 0;
}
