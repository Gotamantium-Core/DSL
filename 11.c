#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int start;
    int size;
    int freeFlag;
    struct Node *next;
} Node;

void AddProcess(Node* *head, int start, int size, int freeFlag) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->start = start;
    new->size = size;
    new->freeFlag = freeFlag;
    new->next = NULL;
    if (*head == NULL) {
        *head = new;
        return;
    }
    Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

void freeProcess(Node *head, int start) {
    Node* temp = head;
    while (temp) {
        if (temp->start == start && !temp->freeFlag) {
            temp->freeFlag = 1; // free it
            
            // merging with next (if also free)
            if (temp->next && temp->next->freeFlag) {
                temp->size += temp->next->size;
                Node *del = temp->next;
                temp->next = del->next;
                free(del); // merged
            }
            return;
        }
        temp = temp->next;
    }
}

Node* firstFit(Node* head, int size) {
    Node *temp = head;
    while (temp) {
        if (temp->freeFlag && temp->size >= size) {
            // allocate
            if (temp->size > size) {
                // new is leftover memory
                Node *new = (Node *) malloc(sizeof(Node));
                new->start = temp->start + size;
                new->size = temp->size - size;
                new->freeFlag = 1;
                new->next = temp->next;
                temp->next = new;
                temp->size = size;
            }
            temp->freeFlag = 0;
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // space not available
}

Node* bestFit(Node *head, int size) {
    Node* temp = head, *best = NULL;
    while (temp) {
        if (temp->freeFlag && temp->size >= size) 
            if (best == NULL || temp->size < best->size)
                best = temp;
        temp = temp->next;
    }
    
    if (!best) return NULL;
    
    // new is leftover memory
    if (best->size > size) {
        Node *new = (Node *) malloc(sizeof(Node));
        new->start = best->start + size;
        new->size = best->size - size;
        new->freeFlag = 1;
        new->next = best->next;
        best->next = new;
        best->size = size;
    }
    best->freeFlag = 0;
    return best;
}

Node* worstFit(Node *head, int size) {
    Node *temp = head, *worst = NULL;
    while (temp) {
        if (temp->freeFlag && temp->size >= size)
            if (worst == NULL || temp->size > worst->size)
                worst = temp;
        temp = temp->next;
    }
    if (!worst) return NULL;
    
    // new is leftover memory
    if (worst->size > size) {
        Node* new = (Node *) malloc(sizeof(Node));
        new->start = worst->start + size;
        new->size = worst->size - size;
        new->freeFlag = 1;
        
        new->next = worst->next;
        worst->next = new;
        worst->size = size;
    }
    worst->freeFlag = 0;
    return worst;
}

void disp(Node* head) {
    Node *temp = head;
    while (temp) {
        printf("[%d-%d: %d KB %s]\n", temp->start, temp->start + temp->size, temp->size, temp->freeFlag ? "free" : "used");
        temp = temp->next;
    }
    printf("\n");
}

Node* allocate(Node* head, int size, int fit) {
    Node* alloc = NULL;
    if (fit == 1) alloc = firstFit(head, size);
    else if (fit == 2) alloc = bestFit(head, size);
    else if (fit == 3) alloc = worstFit(head, size);
    else {
        printf("Invalid fit\n");
        return NULL;
    }
    
    if (!alloc)
        printf("Memory could not be allocated\n");
    return alloc;
}

int main() {
    Node* mem = NULL;
    AddProcess(&mem, 0, 10, 0);
    AddProcess(&mem, 10, 300, 1);
    AddProcess(&mem, 310, 90, 0);
    AddProcess(&mem, 400, 600, 1);
    AddProcess(&mem, 1000, 500, 0);
    AddProcess(&mem, 1500, 350, 1);
    AddProcess(&mem, 1850, 150, 0);
    AddProcess(&mem, 2000, 200, 1);
    AddProcess(&mem, 2200, 100, 0);
    AddProcess(&mem, 2300, 850, 1);
    AddProcess(&mem, 3150, 350, 0);
    AddProcess(&mem, 3500, 500, 1);
    disp(mem);
    return 0;
}