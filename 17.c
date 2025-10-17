#include <stdio.h>
#include <stdlib.h>

typedef struct State {
    int a, b, c;
    int parentIndex;
} State;

typedef struct Queue {
    State* arr;
    int front, rear, capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = malloc(sizeof(Queue));
    q->arr = malloc(sizeof(State) * capacity);
    q->capacity = capacity;
    q->front = 0;
    q->rear = 0;
    return q;
}

void enqueue(Queue* q, State s) {
    if (q->rear >= q->capacity) {
        printf("Queue overflow!\n");
        exit(1);
    }
    q->arr[q->rear++] = s;
}

State dequeue(Queue* q) {
    return q->arr[q->front++];
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void freeQueue(Queue* q) {
    free(q->arr);
    free(q);
}

int isVisited(int a, int b, int c, int visited[11][8][5]) {
    return visited[a][b][c];
}

void markVisited(int a, int b, int c, int visited[11][8][5]) {
    visited[a][b][c] = 1;
}

void pour(State curr, int from, int to, int caps[3], int visited[11][8][5], Queue* q, int parentIndex) {
    int jug[3] = {curr.a, curr.b, curr.c};

    int pour_amt = (jug[from] < (caps[to] - jug[to])) ? jug[from] : (caps[to] - jug[to]);
    jug[from] -= pour_amt;
    jug[to] += pour_amt;

    if (!isVisited(jug[0], jug[1], jug[2], visited)) {
        markVisited(jug[0], jug[1], jug[2], visited);
        State next = {jug[0], jug[1], jug[2], parentIndex};
        enqueue(q, next);
    }
}

void printPath(Queue* q, int index) {
    State path[1000];
    int len = 0;

    while (index != -1) {
        path[len++] = q->arr[index];
        index = q->arr[index].parentIndex;
    }

    printf("Sequence:\n");
    for (int i = len - 1; i >= 0; i--)
        printf("(%d, %d, %d)\n", path[i].a, path[i].b, path[i].c);
}

int main() {
    int caps[3] = {10, 7, 4};
    int visited[11][8][5] = {0};

    Queue* q = createQueue(1000);

    State start = {10, 0, 0, -1};
    enqueue(q, start);
    markVisited(10, 0, 0, visited);

    while (!isEmpty(q)) {
        int idx = q->front;
        State curr = dequeue(q);

        if (curr.a == 2 || curr.b == 2 || curr.c == 2) {
            printf("Goal reached!\n");
            printPath(q, idx);
            freeQueue(q);
            return 0;
        }

        for (int from = 0; from < 3; from++)
            for (int to = 0; to < 3; to++)
                if (from != to)
                    pour(curr, from, to, caps, visited, q, idx);
    }

    printf("No solution found.\n");
    freeQueue(q);
    return 0;
}
