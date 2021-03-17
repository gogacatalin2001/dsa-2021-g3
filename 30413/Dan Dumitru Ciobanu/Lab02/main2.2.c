#include <stdio.h>
#include <stdlib.h>

struct node* startG = NULL;
struct node* startR = NULL;

void traverse(struct node *start)
{
	struct node* temp;

	/// check if list empty
	if (start == NULL)
		printf("\nList is empty\n");

	///  not empty => print
	else {
		temp = start;
		while (temp != NULL) {
			printf("Data = %d\n",
				temp->info);
			temp = temp->link;
		}
	}
}

void insertAtFront(int data, struct node *start)
{
	struct node* temp;
	temp = malloc(sizeof(struct node));
	temp->info = data;
	temp->link = start;
	start = temp;
}

void insertAtEnd(int data, struct node *start)
{
	struct node *temp, *head;
	temp = malloc(sizeof(struct node));

	/// Changes next nodes
	temp->link = 0;
	temp->info = data;
	head = start;
	while (head->link != NULL) {
		head = head->link;
	}
	head->link = temp;
}

void deleteFirst(struct node *start)
{
	struct node* temp;
	if (start == NULL)
		printf("\nList is empty\n"); /// check if empty
	else {
		temp = start;
		start = start->link;
		free(temp);
	}
}

void deleteEnd(struct node *start)
{
	struct node *temp, *prevnode;
	if (start == NULL)
		printf("\nList is Empty\n"); /// check if empty
	else {
		temp = start;
		while (temp->link != 0) {
			prevnode = temp;
			temp = temp->link;
		}
		free(temp);
		prevnode->link = 0;
	}
}

int main()
{
    return 0;
}
