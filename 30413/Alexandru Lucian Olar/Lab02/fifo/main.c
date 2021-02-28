#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    unsigned int truck_id;
    struct node *next;
} NodeT;

typedef struct {
    int count;
    NodeT *first;
    NodeT *last;
} HeaderT;

void CreateList(HeaderT *list) {
    list->count = 0;
    NodeT *last = (NodeT *)malloc(sizeof(NodeT)); last->next = NULL;
    NodeT *first = (NodeT *)malloc(sizeof(NodeT)); first->next = last;
    list->first = first; list->last = last;
}

void push(HeaderT *list, unsigned int truck_id) {
    NodeT *newNode = (NodeT *)malloc(sizeof(NodeT));
    if (newNode) {
        newNode->truck_id = truck_id;
        newNode->next = list->first->next;
    }
    list->first->next = newNode;
    list->count++;
}



void pop2(HeaderT *list){
    if(list->first->next==list->last)
        return;
     NodeT *cpy = list->first->next;
     while (cpy->next != NULL){
        if(cpy->next->next==list->last)
        break;

        cpy = cpy->next;
     }
        cpy->next=list->last;


}


int removeElement(HeaderT *list, unsigned int truck_id) {
    NodeT *cpy = list->first->next;
    NodeT *cpy1 = NULL;
    while (cpy->next != NULL) {
        if (cpy->truck_id == truck_id)
            break;
        cpy1 = cpy;
        cpy = cpy->next;
    }
    if (cpy == NULL)
        return 0;
    cpy1->next = cpy->next;
    list->count--;
    free(cpy);
    return 1;
}

void printStack(const HeaderT *list) {
    NodeT *cpy = list->first->next;
    while (cpy->next != NULL) {
        printf("%i ", cpy->truck_id);
        cpy = cpy->next;
    }
    printf("\n");
}

void R(HeaderT *road, unsigned int truck_id) {
    push(road, truck_id);
}

NodeT *find(HeaderT *list, unsigned int element) {
    NodeT *el = list->first->next;
    while (el->next != NULL) {
        if (el->truck_id == element)
            return el;
        el = el->next;
    }
    return NULL;
}

void E(HeaderT *garrage, HeaderT *road, unsigned int truck_id) {
    NodeT *truck = find(road, truck_id);
    if (truck == NULL)
        return;
    push(garrage, truck->truck_id);
    removeElement(road, truck->truck_id);
}


int X2(HeaderT *garrage, HeaderT *road,  unsigned int truck_id) {
    NodeT *truck = find(road, truck_id);
    if (truck == NULL)
        return;
    pop2(garrage);
    push(road, truck->truck_id);

}


void S(char mode, HeaderT *road, HeaderT *garrage) {
    switch (mode) {
        case 'R':
            printStack(road);
            break;
        case 'G':
            printStack(garrage);
            break;
        default:
            printf("Wrong mode selected\n");
    }
}

int chToInt(char *string) {
    int num=0;
    int p=0;
    int i;
    for (i=strlen(string)-3;string[i]!='(';--i) {
        num = num + ((string[i]-'0')*pow(10, p++));
    }
    return num;
}

int main() {
    HeaderT *garrage = (HeaderT *)malloc(sizeof(HeaderT));
    CreateList(garrage);

    HeaderT *road = (HeaderT *)malloc(sizeof(HeaderT));
    CreateList(road);

    FILE *input = fopen("date.in", "r");

    char *command = (char *)malloc(100 * sizeof(char));

    while (!feof(input)) {
        fgets(command, 100, input);
        switch (command[0]) {
            case 'R':
                R(road, chToInt(command));
                break;
            case 'E':
                E(garrage, road, chToInt(command));
                break;
            case 'X':
                X2(garrage,road, chToInt(command));
                break;
            case 'S':
                S(command[2], road, garrage);
                break;
            default:
                printf("Wrong mode selected\n");
        }
    }

    free(command);
    fclose(input);
    return 0;
}
