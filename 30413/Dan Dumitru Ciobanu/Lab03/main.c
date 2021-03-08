#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    char word[10];
    int NrOfOccurances;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct DList{
    int count;
    Node *first;
    Node *last;
}DList;

bool isEmpty(DList *listPtr)
{
    if(listPtr -> count == 0)
        return 1;
    return 0;
}

DList* New_DLL(){
    DList *listPtr = (DList*)malloc(sizeof(DList));
    if (listPtr){
        listPtr->count = 0;
        listPtr->first = NULL;
        listPtr->last = NULL;
    }
    return listPtr;
}

Node* newnode(char word[]){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode){
        strcpy(newNode -> word, word);
        newNode -> NrOfOccurances = 1;
        newNode -> next = NULL;
        newNode -> prev = NULL;
    }
    return newNode;
}

int NodesComparing( Node* node1, Node* node2 ){
    return strcmp(node1->word,node2->word);
}



int insert(DList* listPtr, Node* node){

    if (listPtr){
        if (isEmpty(listPtr)){
            listPtr->first = listPtr->last = node;
            node->prev = node->next = NULL;
        }
        else{
            Node *currentNode = listPtr->first;
            int i=0;
            while(NodesComparing(node, currentNode)>0 && currentNode->next!=NULL){
                currentNode = currentNode->next;
                i++;
            }
            printf("debug: %s %s %d\n",currentNode->word,node->word,i);
            if(NodesComparing(node, currentNode)<0){
                if (currentNode->prev == NULL)
                    listPtr->first = node;
                node->prev =  currentNode->prev;
                node->next = currentNode;
                currentNode->prev = node;
                node->prev->next = node;
            }
            if(NodesComparing(node, currentNode)==0){
                currentNode->NrOfOccurances++;
            }
            if(NodesComparing(node, currentNode)>0){
                if (currentNode->next == NULL)
                    listPtr->last = node;
                node->prev =  currentNode;
                node->next = currentNode->next;
                currentNode->next = node;
            }
        }
        listPtr->count++;
        return 1;
    }
    return 0;

}

void ascendingPrinting(DList* listPtr, FILE* w){
    Node *p;
    for(p=listPtr->first; p!=NULL; p=p->next)
        fprintf(w,"%s:%d\n",p->word,p->NrOfOccurances);

}

void descendingPrinting(DList* listPtr, FILE* w){
    Node *p;
    for(p=listPtr->last; p!=NULL; p=p->prev)
        fprintf(w,"%s:%d\n",p->word,p->NrOfOccurances);

}

int main(int argc, char* argv[]){

    FILE *r, *w;
    r = fopen(argv[1], "r");
    w = fopen(argv[2], "w");
    DList *Word_List = New_DLL();
    char buffer[10];
    while(fscanf(r,"%s",buffer)!=EOF){
        insert(Word_List,newnode(buffer));
    }
    ascendingPrinting(Word_List, w);
    descendingPrinting(Word_List, w);

    return 0;
}
