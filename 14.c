#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;
    int p;
    struct Node* next;
} Node;

Node* createNew(int num, int p) {
    Node* new = (Node *) malloc(sizeof(Node));
    new->num = num;
    new->p = p;
    new->next = NULL;
    return new;
}

void insert(Node* *head, int num, int p) {
    Node* new = createNew(num, p);
    if (*head == NULL || (*head)->p < p) {
        new->next = *head;
        *head = new;
        return;
    }
    Node *prev = NULL, *temp = *head;
    while (temp && temp->p <= p) {
        prev = temp;
        temp = temp->next;
    }
    new->next = temp;
    if (prev) prev->next = new;
    else *head = new;
}

int Serve(Node* *head) {
    if (*head == NULL) return -1;
    Node* temp = *head;
    *head = (*head)->next;
    int ret = temp->num;
    free(temp);
    return ret;
}

void disp(Node* head) {
    if (head == NULL) {
        printf("Queue empty\n");
        return;
    }
    while (head) {
        printf("%d : %d <- ", head->num, head->p);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    int func, n, p, token=100;
    printf("Enter number of customers: ");
    scanf("%d", &n);
    printf("Priority: \nDisabled = 4\nDefence = 3\nSenior = 2\n None of the above = 1\n");
    for (int i=0; i < n; i++) {
        printf("Enter customer %d's priority: ", i+1);
        scanf("%d", &p);
        insert(&head, token++, p);
    }
    while (1) {
        printf("1. Serve\n2. Show queue\n0. Exit\n");
        printf("Enter function: ");
        scanf("%d", &func);
        
        if (0 == func) break;
        else if (1 == func) {
            int del = Serve(&head);
            if (del != -1) printf("%d served!\n", del);
            else printf("All people served!\n");
        } else if (2 == func) {
            disp(head);
        } else {
            printf("Invalid function\n");
        }
    }
    return 0;
}