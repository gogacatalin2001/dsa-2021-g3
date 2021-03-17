#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    int aparitii;
    char *word;
    struct node *prev;
    struct node *next;
} NodeT;

typedef struct {

    int count;
    NodeT *first;
    NodeT *last;

} DLListT;

DLListT *createList() {
    DLListT *list = (DLListT *)malloc(sizeof(DLListT));
    if (list) {
        list->count = 0;
        NodeT *first = (NodeT *)malloc(sizeof(NodeT));
        NodeT *last = (NodeT *)malloc(sizeof(NodeT));
        if (first && last) {
            first->prev = NULL; first->next = last;
            last->prev = first; last->next = NULL;
            list->first = first; list->last = last;
        }
    }
    return list;
}

NodeT *createNodeT() {
    NodeT *newNode = (NodeT *)malloc(sizeof(NodeT));
    if (newNode) {
        newNode->aparitii = 0;
        newNode->word = (char *)malloc(100 * sizeof(char));
        newNode->prev = newNode->next = NULL;
    }
    return newNode;
}

NodeT *find( DLListT *list,  char *word) {
    NodeT *node = list->first->next;
    while (node->next != NULL && strcmp(tolower(node->word), tolower(word)) < 0)
        node = node->next;
    return node;
}




void insertWord(DLListT *list,  char *word) {
    NodeT *foundNode = find(list, word);
    if (foundNode != list->last && strcmp(tolower(foundNode->word), tolower(word)) == 0) {

        ++foundNode->aparitii;
    } else {
        NodeT *newNode = createNodeT();
        ++newNode->aparitii;
        strcpy(newNode->word, word);

        newNode->next = foundNode;
        newNode->prev = foundNode->prev;
        foundNode->prev->next = newNode;
        foundNode->prev = newNode;

        ++list->count;
    }
}

void fprintList(FILE *output,  DLListT *list) {
    fprintf(output, "%d  \n", list->count);
    NodeT *node = list->first->next;
    while (node->next != NULL) {
        fprintf(output, "%s: %d   \n", node->word, node->aparitii);
        node = node->next;
    }
}

void fprintDescList(FILE *output, const DLListT *list) {
    fprintf(output, "%d \n", list->count);
    NodeT *node = list->last->prev;
    while (node->prev != NULL) {
        fprintf(output, "%s:  %d \n", node->word, node->aparitii);
        node = node->prev;
    }
}

int main() {
    FILE *input = fopen("date.in", "r");

    DLListT *freqList = createList();

    while (!feof(input)) {
        char *word = (char *)malloc(100 * sizeof(char));
        fscanf(input, "%s ", word);
        insertWord(freqList, word);
        free(word);
    }

    FILE *out = fopen("date.out", "w");
    fprintList(out, freqList);
    fprintf(out,"\n");
    fprintDescList(out, freqList);
    fclose(out);

    fclose(input);
    return 0;
}
