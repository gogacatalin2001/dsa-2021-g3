#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
   char word[100];
   int frequency;
    struct node *next;
    struct node *prev;
} NodeT;

typedef struct{
    int count;
    NodeT *first;
    NodeT *last;
} DLListT;

NodeT *createDLLNode(char *word){
    NodeT *p=(NodeT *)malloc(sizeof(NodeT));
    if (p){
        strcpy(p->word, word);
        //p->word=word;
        p->next=p->prev=NULL;
    }
    return p;
}

DLListT *createEmptyDLL(){
    DLListT *listPtr=(DLListT*) malloc(sizeof(DLListT));
    if (listPtr){
        listPtr->count=0;
        listPtr->first=listPtr->last=NULL;
    }
    return listPtr;
}

int isEmpty(DLListT *listPtr){
    return (listPtr->count==0 && listPtr->first==NULL && listPtr->first==NULL);
}

int insertAtFront(DLListT *listPtr, NodeT *p){
    if (listPtr){
        if (isEmpty(listPtr)){
            listPtr->first = listPtr->last = p;
            p->prev = p->next = NULL;
            }
        else{
            p->next = listPtr->first;
            listPtr->first->prev = p;
            p->prev=NULL;
            listPtr->first=p;
            }
        p->frequency=1;
        }
}

void printList(const DLListT *list) {
    NodeT *cpy = list->first;
    while (cpy != NULL) {
        printf("%s ", cpy->word);
        cpy = cpy->next;
        }
    printf("\n");
}

int freq(DLListT *listPtr, char *word){
    NodeT *cpy = listPtr->first;
    while (cpy != NULL) {
        if (!strcmp(cpy->word,word)){
            cpy->frequency++;
            return 1;
            }
        cpy = cpy->next;
        }
    return 0;
}

void print_ordered_words(DLListT *listPtr){

    for (int i=1;i<=listPtr->count;++i){
        NodeT *cpy=listPtr->first;
        NodeT *cpy2=listPtr->first;
        while (cpy != NULL) {
            if (strcmp(cpy->word,cpy2->word)>0 && cpy->frequency!=-1)
                cpy2=cpy;
            cpy = cpy->next;
            }
        printf("%s %d\n",cpy2->word, cpy2->frequency);
        cpy2->frequency=-1;
        }
}

int main(int argc, char *arcv[])
{
    FILE *in=fopen(arcv[1], "r");
    DLListT *list_ptr=createEmptyDLL();
    do {
        char *word=(char *)malloc(100*sizeof(char));
        fscanf(in, "%s ", word);
        NodeT *ptr=createDLLNode(word);
        if (freq(list_ptr, word)==0)
            insertAtFront(list_ptr, ptr);
        free(word);
    } while (!feof(in));

    print_ordered_words(list_ptr);


    return 0;
}
