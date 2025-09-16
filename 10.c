#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char name[50];
    int freq;
    struct Node *next;
} Node;

void ShowAll(Node *);
Node* createNew(char *, int);
void priorityAdd(Node **, Node *);
void newApp(Node **, char *);
void incFrequency(Node **, char *);
void clean(Node **);

int main() {
    Node* head = NULL;
    char name[50];
    int func;
    printf("No apps open yet\n");
    while (1) {
        printf("1. Open app \n2. Clean \n3. Open new app \n0. Quit\n");
        printf("Enter function: ");
        scanf("%d", &func);
        
        if (0 == func) break;
        else if (1 == func) {
            printf("Enter name of app: ");
            scanf(" %[^\n]", name);
            incFrequency(&head, name);
            
        } else if (2 == func) {
            clean(&head);
        } else if (3 == func) {
            printf("Enter new app's name: ");
            scanf(" %[^\n]", name);
            newApp(&head, name);
        } else
            printf("Invalid function\n");
        ShowAll(head); 
    }
    return 0;
}

Node* createNew(char *name, int freq) {
    Node* new = (Node *) malloc(sizeof(Node));
    strcpy(new->name, name);
    new->freq = freq;
    new->next = NULL;
    return new;
}
void priorityAdd(Node* *head, Node* new) {
    if (*head == NULL || (*head)->freq > new->freq) {
        new->next = *head;
        *head = new;
        return;
    }
    Node *prev = NULL, *curr = *head;
    while (curr && curr->freq <= new->freq) {
        prev = curr;
        curr = curr->next;
    }
    new->next = curr;
    prev->next = new;
}
void newApp(Node* *head, char* name) {
    Node* temp = *head;
    while (temp) {
        if (0 == strcmp(temp->name, name)) {
            printf("App already exists\n");
            return;
        }
        temp = temp->next;
    }
    Node* new = createNew(name, 1);
    priorityAdd(head, new);
}
void incFrequency(Node** head, char *name) {
    if (*head == NULL) return;
    Node* prev = NULL, *curr = *head;
    while (curr && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        printf("App %s not found!\n", name);
        return;
    }

    if (prev) 
        prev->next = curr->next;
    else 
        *head = curr->next;
    curr->freq++;
    curr->next = NULL;
    priorityAdd(head, curr);
}
void clean(Node** head) {
    if (*head == NULL) {
        printf("Empty\n");
        return;
    }
    int min = (*head)->freq;
    Node* temp = *head;
    while (temp && temp->freq == min) {
        Node* del = temp;
        printf("Removed: %s (freq = %d)\n", del->name, del->freq);
        temp = temp->next;
        free(del);
    }
    *head = temp;
}
void ShowAll(Node* head) {
    printf("Current apps: ");
    while (head) {
        printf("[%s:%d] -> ", head->name, head->freq);
        head = head->next;
    }
    printf("NULL\n");
}
