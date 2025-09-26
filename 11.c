#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int start, size, f;
    struct Node* next;
} Node;

void addProcess(Node** head, int start, int size, int f) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->start = start;
    newNode->size = size;
    newNode->f = f;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

void freeProcess(Node** head, int start) {
    Node *temp = *head, *prev = NULL;
    while (temp) {
        if (temp->start == start && !temp->f) {
            temp->f = 1;
            // merge with next
            if (temp->next && temp->next->f) {
                Node* del = temp->next;
                temp->size += del->size;
                temp->next = del->next;
                free(del);
            }
            // merge with previous
            if (prev && prev->f) {
                prev->size += temp->size;
                prev->next = temp->next;
                free(temp);
                temp = prev;
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

Node* allocateBlock(Node** head, int size, Node* block) {
    if (!block) return NULL;
    if (block->size > size) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->start = block->start + size;
        newNode->size = block->size - size;
        newNode->f = 1;
        newNode->next = block->next;
        block->next = newNode;
        block->size = size;
    }
    block->f = 0;
    return block;
}

Node* firstFit(Node** head, int size) {
    Node* temp = *head;
    while (temp) {
        if (temp->f && temp->size >= size)
            return allocateBlock(head, size, temp);
        temp = temp->next;
    }
    return NULL;
}

Node* bestFit(Node** head, int size) {
    Node* temp = *head;
    Node* best = NULL;
    while (temp) {
        if (temp->f && temp->size >= size) {
            if (!best || temp->size < best->size)
                best = temp;
        }
        temp = temp->next;
    }
    return allocateBlock(head, size, best);
}

Node* worstFit(Node** head, int size) {
    Node* temp = *head;
    Node* worst = NULL;
    while (temp) {
        if (temp->f && temp->size >= size) {
            if (!worst || temp->size > worst->size)
                worst = temp;
        }
        temp = temp->next;
    }
    return allocateBlock(head, size, worst);
}

Node* allocate(Node** head, int size, int strategy) {
    if (strategy == 1) return firstFit(head, size);
    if (strategy == 2) return bestFit(head, size);
    if (strategy == 3) return worstFit(head, size);
    printf("Invalid strategy\n");
    return NULL;
}

Node* copyMap(Node* old) {
    Node* newHead = NULL;
    Node* temp = old;
    while (temp) {
        addProcess(&newHead, temp->start, temp->size, temp->f);
        temp = temp->next;
    }
    return newHead;
}

void disp(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("[%d - %d] (%d KB) %s\n", temp->start, temp->start + temp->size, temp->size, temp->f ? "free" : "in use");
        temp = temp->next;
    }
    printf("\n");
}

void analyze(Node* head, char* method) {
    int freeBlocks = 0, freeMem = 0;
    Node* temp = head;
    while (temp) {
        if (temp->f) {
            freeBlocks++;
            freeMem += temp->size;
        }
        temp = temp->next;
    }
    printf("(%s)\nNumber of free blocks: %d\nFree memory: %d KB\n\n", method, freeBlocks, freeMem);
}

int main() {
    Node* mem = NULL;
    // Initial memory map (used/free)
    addProcess(&mem, 0, 10, 0); // P5 (used)
    addProcess(&mem, 10, 300, 1);
    addProcess(&mem, 310, 90, 0); // P6 (used)
    addProcess(&mem, 400, 600, 1);
    addProcess(&mem, 1000, 500, 0); // P1 (used)
    addProcess(&mem, 1500, 350, 1);
    addProcess(&mem, 1850, 150, 0); // P2 (used)
    addProcess(&mem, 2000, 200, 1);
    addProcess(&mem, 2200, 100, 0); // P4 (used)
    addProcess(&mem, 2300, 850, 1);
    addProcess(&mem, 3150, 350, 0); // P3 (used)
    addProcess(&mem, 3500, 499, 1);

    Node* memFF = copyMap(mem);
    Node* memBF = copyMap(mem);
    Node* memWF = copyMap(mem);

    Node *p7FF,*p10FF,*p8FF,*p9FF;
    Node *p7BF,*p10BF,*p8BF,*p9BF;
    Node *p7WF,*p10WF,*p8WF,*p9WF;

    printf("=== First Fit ===\n");
    p7FF = allocate(&memFF,115,1); disp(memFF);
    p10FF = allocate(&memFF,650,1); disp(memFF);
    freeProcess(&memFF,3150); disp(memFF); // P3 done
    freeProcess(&memFF,1000); disp(memFF); // P1 done
    freeProcess(&memFF,310); disp(memFF); // P6 done
    p8FF = allocate(&memFF,200,1); disp(memFF); // P8
    freeProcess(&memFF,0); disp(memFF); // P5 done
    freeProcess(&memFF,1850); disp(memFF); // P2 done
    p9FF = allocate(&memFF,37,1); disp(memFF); // P9
    freeProcess(&memFF,p10FF->start); disp(memFF); // P10 done
    freeProcess(&memFF,p9FF->start); disp(memFF); // P9 done
    freeProcess(&memFF,2200); disp(memFF); // P4 done

    analyze(memFF,"First fit");

    printf("=== Best Fit ===\n");
    p7BF = allocate(&memBF,115,2); disp(memBF);
    p10BF = allocate(&memBF,650,2); disp(memBF);
    freeProcess(&memBF,3150); disp(memBF);
    freeProcess(&memBF,1000); disp(memBF);
    freeProcess(&memBF,310); disp(memBF);
    p8BF = allocate(&memBF,200,2); disp(memBF);
    freeProcess(&memBF,0); disp(memBF);
    freeProcess(&memBF,1850); disp(memBF);
    p9BF = allocate(&memBF,37,2); disp(memBF);
    freeProcess(&memBF,p10BF->start); disp(memBF);
    freeProcess(&memBF,p9BF->start); disp(memBF);
    freeProcess(&memBF,2200); disp(memBF);

    analyze(memBF,"Best fit");

    printf("=== Worst Fit ===\n");
    p7WF = allocate(&memWF,115,3); disp(memWF);
    p10WF = allocate(&memWF,650,3); disp(memWF);
    freeProcess(&memWF,3150); disp(memWF);
    freeProcess(&memWF,1000); disp(memWF);
    freeProcess(&memWF,310); disp(memWF);
    p8WF = allocate(&memWF,200,3); disp(memWF);
    freeProcess(&memWF,0); disp(memWF);
    freeProcess(&memWF,1850); disp(memWF);
    p9WF = allocate(&memWF,37,3); disp(memWF);
    freeProcess(&memWF,p10WF->start); disp(memWF);
    freeProcess(&memWF,p9WF->start); disp(memWF);
    freeProcess(&memWF,2200); disp(memWF);

    analyze(memWF,"Worst fit");
    return 0;
}

