#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char url[100];
    struct Node* next;
} Node;

void push(Node** top, char* url) {
    Node* new = (Node *) malloc(sizeof(Node));
    strcpy(new->url, url);
    new->next = *top;
    *top = new;
}

int pop(Node** top, char* url) {
    if (*top == NULL)
        return 0;
    
    Node* temp = *top;
    strcpy(url, temp->url);
    *top = (*top)->next;
    free(temp);
    return 1;
}

void visit(Node** back, Node** forward, char* current, char* url) {
    if (strlen(current) > 0)
        push(back, current);
    strcpy(current, url);

    char temp[100];
    while (pop(forward, temp));

    printf("Visited: %s\n", current);
}

void goBack(Node** back, Node** forward, char* current) {
    char temp[100];
    if (pop(back, temp)) {
        push(forward, current);
        strcpy(current, temp);
        printf("Back to: %s\n", current);
        return;
    }
    printf("End of history\n");
}

void goForward(Node** back, Node** forward, char* current) {
    char temp[100];
    if (pop(forward, temp)) {
        push(back, current);
        strcpy(current, temp);
        printf("Moved to: %s", current);
        return;
    }
    printf("No more pages in forward history\n");
}

int main() {
    Node* back = NULL, *front = NULL;
    char current[] = "https://ktu.edu.in";
    int func;
    printf("Starting at %s\n", current);
    while (1) {
        printf("1. Visit new site \n2. Go back \n3. Go forward \n0. Exit\n");
        printf("Enter function: ");
        scanf("%d", &func);

        if (0 == func) break;
        else if (1 == func) {
            char url[100];
            printf("Enter url: ");
            scanf(" %s", url);
            visit(&back, &front, current, url);
        } else if (2 == func) {
            goBack(&back, &front, current);
        } else if (3 == func) {
            goForward(&back, &front, current);
        } else {
            printf("Invalid function\n");
        }
    }
    return 0;

}
