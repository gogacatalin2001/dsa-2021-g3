#include <stdio.h>
#include <stdlib.h>
typedef struct road
{
    char truck_id;
    struct road *next;
}Road;
typedef struct garage
{
    int truck_id;
    struct road *next;
}Garage;
void add(Road *head, int data)
{
    Road *ptr;
    Road *newNode = (Road*)malloc(sizeof(Road));
    newNode->truck_id = data;
    newNode->next = NULL;
    ptr = head;
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = newNode;
}

void print(Road *head)
{
    if(head == NULL) printf("the list is empty");
    Road *ptr;
    ptr = head;
    while(ptr != NULL)
    {
        printf("%d ", ptr->truck_id);
        ptr = ptr->next;
    }
}
int main()
{
    int n, i;
    char s;
    FILE *f = fopen("in.txt", "r");
    fscanf(f, "%d", &n);

    char *Nr = (char*)malloc(n*sizeof(char));
    char *Com = (char*)malloc(n*sizeof(char));
    s = getc(f);
    while(s  != '\n')
    {
        for(i = 0; i < n; i++)
    {

        *(Com + i) = getc(f);
        fscanf(f, "%d",  *(Nr + i));}
    }


    Road *head = (Road*)malloc(sizeof(Road));
    i = 0;
        if(*(Com + i) == 'R')
        {
            head->truck_id = *(Nr + i);
            head->next = NULL;

        }
    i++;
    while(*(Com + i) == 'R')
    {
        Road *newNode = (Road*)malloc(sizeof(Road));
        newNode->truck_id = *(Nr + i);
        newNode->next = NULL;
        add(head, newNode->truck_id);
        i++;
    }


    while(*(Com + i) == 'S')
    {
        if((char)*(Nr + i) == 'R') print(head);
        i++;
    }
    Garage *headG = (Garage*)malloc(sizeof(Garage));
    if(*(Com + i) == 'E')
        {
            headG->truck_id = *(Nr + i);
            headG->next = NULL;

        }
        i++;
    while(*(Com + i) == 'E')
    {
        Garage *newNode = (Garage*)malloc(sizeof(Garage));
        newNode->truck_id = *(Nr + i);
        newNode->next = NULL;
        add(headG, newNode->truck_id);
        i++;
    }
    print(headG);
    fclose(f);
    return 0;
}
