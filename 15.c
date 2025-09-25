#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next; 
} Node;

typedef struct Heapnode {
    int value;
    Node* node;
} Heapnode;

typedef struct MinHeap {
    Heapnode *arr;
    int size;
    int capacity;
} MinHeap;

Node* createNode(int data) {
    Node* new = (Node *) malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    return new;
}

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap *) malloc(sizeof(MinHeap));
    heap->arr = (Heapnode *) malloc(capacity * sizeof(Heapnode));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap(Heapnode *a, Heapnode *b) {
    Heapnode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap *heap, int i) {
    int smallest = i;
    int left = 2*i+1, right = 2*i+2;
    if (left < heap->size && heap->arr[smallest].node->data > heap->arr[left].node->data)
        smallest = left;
    if (right < heap->size && heap->arr[smallest].node->data > heap->arr[right].node->data)
        smallest = right;
        
    if (smallest != i) {
        swap(&heap->arr[smallest], &heap->arr[i]);
        heapify(heap, smallest);
    }
}

void insert(MinHeap* heap, Heapnode node) {
    heap->arr[heap->size] = node;
    heap->size++;
    
    // Bubble up
    int i=heap->size-1;
    while (i != 0 && heap->arr[(i - 1)/2].value > heap->arr[i].value) {
        swap(&heap->arr[i], &heap->arr[(i - 1)/2]);
        i = (i - 1)/2;
    } 
}

Heapnode extractMin(MinHeap *heap) {
    Heapnode root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size-1];
    heap->size--;
    heapify(heap, 0);
    return root;
}

Node* mergeKLists(Node* *lists, int k) {
    MinHeap* heap = createHeap(k);
    
    for (int i=0; i < k; i++) {
        if (lists[i] != NULL) {
            Heapnode h = {lists[i]->data, lists[i]};
            insert(heap, h);
        }
    }
    
    Node dummy;
    Node *tail = &dummy;
    
    while (heap->size > 0) {
        Heapnode minNode = extractMin(heap);
        tail->next = createNode(minNode.value);
        tail = tail->next;
        
        if (minNode.node->next != NULL) {
            Heapnode nextNode = {minNode.node->next->data, minNode.node->next};
            insert(heap, nextNode);
        }
    }
    return dummy.next;
}

void disp(Node* node) {
    while (node) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
Node* createList() {
    int n, val;
    Node *head = NULL, *tail = NULL;
    printf("Enter number of elements in this list: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &val);
        Node* node = createNode(val);

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}
int main() {
    int k=3;
    Node** lists = (Node**) malloc(sizeof(Node*) * k);
    
    for (int i=0; i < k; i++) {
        printf("Enter list %d:\n", i+1);
        lists[i] = createList();
    }
    
    Node* merged = mergeKLists(lists, k);
    printf("Merged List: ");
    disp(merged);
    
    free(lists);
    return 0;
}