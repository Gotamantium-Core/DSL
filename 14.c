#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int token;
    int p;
} Node;

typedef struct {
    Node* arr;
    int size;
    int capacity;
} Maxheap;

Maxheap* createHeap(int capacity) {
    Maxheap *h = (Maxheap *) malloc(sizeof(Maxheap));
    h->arr = (Node *) malloc(sizeof(Node) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(Maxheap* heap, Node node) {
    heap->arr[heap->size] = node;
    int i = heap->size;
    // bubble up
     while (i > 0 && (
        heap->arr[i].p > heap->arr[(i-1)/2].p || 
       (heap->arr[i].p == heap->arr[(i-1)/2].p && heap->arr[i].token < heap->arr[(i-1)/2].token))) {
        swap(&heap->arr[i], &heap->arr[(i-1)/2]);
        i = (i-1)/2;
    }
    heap->size++;
}

void heapify(Maxheap *heap, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heap->size && (
            heap->arr[left].p > heap->arr[largest].p ||
           (heap->arr[left].p == heap->arr[largest].p &&
            heap->arr[left].token < heap->arr[largest].token)))
        largest = left;

    if (right < heap->size && (
            heap->arr[right].p > heap->arr[largest].p ||
           (heap->arr[right].p == heap->arr[largest].p &&
            heap->arr[right].token < heap->arr[largest].token)))
        largest = right;

    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        heapify(heap, largest);
    }
}

void disp(Maxheap *heap) {
    for (int i=0; i < heap->size; i++) 
        printf("%d : %d -> ", heap->arr[i].token, heap->arr[i].p);
    printf("NULL\n");
}

Node extractMax(Maxheap *heap) {
    if (heap->size <= 0) {
        Node nullNode = {-1, -1};
        return nullNode;
    }
    Node node = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return node;
}

int main() {
    int n, t=100;
    printf("Enter n: ");
    scanf("%d", &n);

    Maxheap *heap = createHeap(n);

    for (int i = 0; i < n; i++) {
        Node node;
        printf("Enter priority of customer %d: ", i+1);
        scanf("%d", &node.p);
        node.token = t++;
        insert(heap, node);
    }

    disp(heap);

    printf("Serving...\n");
    while (heap->size > 0) {
        Node served = extractMax(heap);
        printf("Served: %d (priority %d)\n", served.token, served.p);
    }

    return 0;
}
