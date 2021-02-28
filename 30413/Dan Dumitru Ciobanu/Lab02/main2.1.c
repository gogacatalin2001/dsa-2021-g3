#include <stdio.h>
#include <stdlib.h>

struct node {
	int info;
	struct node* link;
};

struct node* startG = NULL;
struct node* startR = NULL;


void R(int data, struct node *startR)
{
	insertAtEnd(startR);///put a truck on the road
}

void E(int data, struct node *startR, struct node *startG)
{
    insertAtEnd(data, startG);///put the truck in the garage
    deleteFirst(startR);///take it out of the road
}

void S(struct node *start)
{
    traverse(start);///print the list of the trucks either on the road, or in the garage depending on input
}

void X(int data, struct node *startG, struct node *startR)
{
    insertAtFront(data, startR);///put the truck back on the road
    deleteEnd(startG);///and then take it out of the garage, in this order, such that we don't lose data
}

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
    int data;
    char secondchoice, op;
    while (1) {


        printf("Make a choice:\n");
		scanf("%c(%d)", &op, &data);
		switch (op) {

		case 'R':
			{
			    printf("Input the data to be added at the end: ");
			    scanf("%d", &data);
			    R(data, startR);
                break;
			}

        case 'E':
            {
                E(data, startR, startG);
                break;
            }

        case 'X':
            {
                X(data, startG, startR);
                break;
            }

        case 'S':
            {
                printf("G or R?\n");
                scanf("%c", &secondchoice);
                switch(secondchoice){

                    case 'R':
                        {
                            S(startR);
                            break;
                        }

                    case 'G':
                        {
                            S(startG);
                            break;
                        }
                    default:
                        printf("Wrong input!\n");
                }
                break;
            }
            case 'H':
                {
                    printf("EXIT\n");
                    exit(1);
                    break;
                }

		default:
			printf("No such choice.\n\n");
		}
	}




    return 0;
}
