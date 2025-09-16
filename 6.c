#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
	char name[30];
	int num;
	struct Node* next;
};

struct Node *rear = NULL;

void nQ(char * name, int num) {
	struct Node *new = (struct Node *) malloc(sizeof(struct Node));
	strcpy(new->name, name);
	new->num = num;
	if (rear == NULL) {
		rear = new;
		rear->next = rear;
	} else {
		new->next = rear->next;
		rear->next = new;
		rear = new;
	}
}

struct Node* dQ() {
	if (rear == NULL) return NULL;

	struct Node* front = rear->next;
	if (rear == front) rear = NULL;
	else rear->next = front->next;

	return front;
	
}

void Display() {
	if (rear == NULL) {
		printf("Empty queue\n");	
		return;
	}

	struct Node *temp = rear->next;

	printf("Current Q: [");
	do {
		printf("%s = %d forms,  ", temp->name, temp->num);
		temp = temp->next;
	} while (temp != rear->next);
	printf("\b\b\b");
	printf("] \n");
}


int main() {
	int n;
	printf("Enter number of customers: ");
	scanf("%d", &n);

	for (int i=0; i < n; i++) {
		char name[30]; int num;
		printf("Enter token num: ");
		scanf(" %[^\n]", name);

		printf("Enter number of forms: ");
		scanf("%d", &num);

		nQ(name, num);
	}

	int func;
	while (1) {
		printf("1. Serve? \n2. Number of customers \n3. Show queue \n0. Quit\n");
		printf("Enter function: ");
		scanf("%d", &func); 

		if (0 == func) break;
		else if (1 == func) {
			struct Node *c = dQ();
			if (c) {
				printf("Now serving %s: ", c->name);
				c->num--;

				if (c->num > 0) {
					printf("%s has %d more forms\n", c->name, c->num);
					nQ(c->name, c->num);
				} else 
					printf("%s served\n", c->name);
				free(c);
			} else {
				printf("Queue is empty \n");
			}
		} else if (2 == func) {
			if (rear == NULL) printf("Customers = 0\n");
			else {
				int count=0;
				struct Node * temp = rear->next;
				do {
					count++;
					temp = temp->next;
				} while (temp != rear->next);

				printf("Customers = %d\n", count);
			}
		} else if (3 == func) {
			Display();
		} else {
			printf("Invalid function\n");
		}
	}
	return 0;
}

