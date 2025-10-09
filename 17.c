#include <stdio.h>
#include <stdlib.h>

typedef struct State {
	int a, b, c;
	int pa, pb, pc; // parent values
} State;

typedef struct Queue {
	State* arr;
	int front, rear, capacity;
} Queue;

Queue* createQueue(int capacity) {
	Queue* q = malloc(sizeof(Queue));
	q->arr = malloc(sizeof(State) * capacity);
	q->capacity = capacity;
	q->front = -1;
	q->rear = -1;
	return q;
}

void nQ(Queue* q, State s) {
	if (q->rear >= q->capacity) return;
	q->arr[q->rear++] = s;
}

State dQ(Queue* q) {
	return q->arr[q->front++];
}

int empty(Queue* q) {
	return q->front == q->rear;
}

void freeQueue(Queue* q) {
	free(q->arr);
	free(q);
}

int isVisited(int a, int b, int c, int visited[11][8][5]) {
	return visited[a][b][c];
}

void mark(int a, int b, int c, int visited[11][8][5]) {
	visited[a][b][c] = 1;
}

void printPath(Queue* q, State end) {
	State path[1000];
	int len = 0;

	for(State s=end; s.a != -1; ) {
		path[len++] = s;
		int pa = s.pa, pb = s.pb, pc = s.pc;
		int found=0;
		for (int i=0; i < q->rear; i++) {
			if (q->arr[i].a == pa && q->arr[i].b == pb && q->arr[i].c == pc) {
				s = q->arr[i];
				found = 1;
				break;

			}
		}
		if (!found) break;
	}

	printf("Sequence: \n");
	for (int i=len-1; i >= 0; i--) 
		printf("(%d, %d, %d)\n", path[i].a, path[i].b, path[i].c);
}

void pour(State curr, int from, int to, int caps[3], int visited[11][8][5], Queue* q) {
	int jug[3] = {curr.a, curr.b, curr.c};

	int pour_amt = (jug[from] < (caps[to]-jug[to])) ? jug[from] : (caps[to] - jug[to]);
	jug[from] -= pour_amt;
	jug[to] += pour_amt;

	if (!isVisited(jug[0], jug[1], jug[2], visited)) {
		mark(jug[0], jug[1], jug[2], visited);
		State next = {jug[0], jug[1], jug[2], curr.a, curr.b, curr.c};
		nQ(q, next);
	}
}

int main() {
	int caps[3] = {10, 7, 4};
	int visited[11][8][5] = { 0 };

	Queue *q = createQueue(100);
	State start = {0, 7, 4, -1, -1, -1};
	nQ(q, start);

	mark(0, 7, 4, visited);

	while (!empty(q)) {
		State curr = dQ(q);

		if (curr.b == 2 || curr.c == 2) {
			printf("Goal reached\n");
			printPath(q, curr);
			freeQueue(q);
			return 0;
		}

		for (int from = 0; from < 3; from++)
			for (int to = 0; to < 3; to++)
				if (from != to) pour(curr, from, to, caps, visited, q);
	}

	printf("No solution\n");
	freeQueue(q);
	return 0;


}



