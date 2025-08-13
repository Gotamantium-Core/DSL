#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char word[20];
    struct Node* next;
}Node;

Node* createNew(char* w) {
    Node* new = (Node *) malloc(sizeof(Node));
    strcpy(new->word, w);
    new->next = NULL;
    return new;
}
void append(Node* *head, char* w) {
    Node* new = createNew(w);
    if (*head == NULL) {
        *head = new;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
}
void display(Node* head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}
int replace(Node *head, char* term, char* word) {
    int count=0;
    Node* temp = head;
    while (temp != NULL) {
        if (0 == strcmp(temp->word, term)) {
            strcpy(temp->word, word);
            count++;
        }
        temp = temp->next;
    }
    return count;
}

int main() {
    Node* doc = NULL;
    char word[20];
    char term[20], repl[20];
    
    printf("Enter text (type 'EOF' to stop): \n");
    while (1) {
        scanf(" %s", word);
        if (0 == strcmp(word, "EOF"))
            break;
        append(&doc, word);
    }
    printf("Enter term to find: ");
    scanf(" %s", term);
    
    printf("Enter word to replace it with: ");
    scanf(" %s", repl);
    
    
    int count = replace(doc, term, repl);
    
    if (0 == count) {
        printf("Word not found\n");
        return 0;
    }
    
    printf("%d words successfully replaced!\nUpdated document:\n", count);
    display(doc);

    return 0;
}