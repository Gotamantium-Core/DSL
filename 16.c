#include <stdio.h>
#include <stdlib.h>

#define INF 99999

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

typedef struct Node {
	int x, y;
	int dist;
}Node;

typedef struct Minheap {
	Node* arr[200];
	int size;
} Minheap;

void swap(Node** a, Node** b) {
	Node* temp = *a;
	*a = *b;
	*b = temp;
}

void insert(Minheap *heap, Node* node) {
	heap->arr[heap->size] = node;
	int i = heap->size++;
	while (i > 0 && heap->arr[i]->dist < heap->arr[(i-1)/2]->dist) {
		swap(&heap->arr[i], &heap->arr[(i-1)/2]);
		i = (i-1)/2;
	}
}

Node* extractMin(Minheap* heap) {
	if (heap->size == 0) return NULL;
	Node* root = heap->arr[0];
	heap->arr[0] = heap->arr[--heap->size];

	// heapify
	int i=0;
	while (1) {
		int smallest = i;
		int left = 2*i+1, right = 2*i+2;
		if (left < heap->size && heap->arr[smallest]->dist > heap->arr[left]->dist)
			smallest = left;
		if (right < heap->size && heap->arr[smallest]->dist > heap->arr[right]->dist)
			smallest = right;

		if (smallest == i) break;
		swap(&heap->arr[i], &heap->arr[smallest]);
		int i = smallest;
	}
	return root;
}

int isValid(int x, int y, int rows, int cols, char maze[100][100]) {
	return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != '#');
}

int Dijkstra(char maze[100][100], int rows, int cols, int sx, int sy, int ex, int ey) {
	int dist[100][100];
	for (int i=0; i < rows; i++)
		for (int j=0; j < cols; j++)
			dist[i][j] = INF; // distance to every other node is infinity in the beginning
	
	Minheap heap = { .size = 0 };
	Node* start = malloc(sizeof(Node));
	start->x = sx; start->y = sy;
	start->dist = 0;

	insert(&heap, start);

	while (heap.size > 0) {
		Node* curr = extractMin(&heap);

		if (curr->x == ex && curr->y == ey) return curr->dist;

		for (int i=0; i < 4; i++) {
			int nx = curr->x + dx[i];
			int ny = curr->y + dy[i];

			if (isValid(nx, ny, rows, cols, maze) && dist[nx][ny] > curr->dist+1) {
				dist[nx][ny] = curr->dist + 1;
				Node* next = malloc(sizeof(Node));

				next->x = nx; 
				next->y = ny; 
				next->dist = dist[nx][ny];
				insert(&heap, next);
			}
		}
		free(curr);
	}
	return -1; // no path 

}

int main() {
	int rows=8, cols=8;

	char maze[100][100] = {
		{'S', '.', '.', '#'},
		{'#', '#', '.', 'C'},
	}; // define maze here
	

	int sx, sy, ex, ey;
	for (int i=0; i < rows; i++)
		for (int j=0; j < cols; j++) {
			if (maze[i][j] == 'S') {sx = i; sy = j;}
			if (maze[i][j] == 'C') {ex = i; ey = j;}
		}

	int dist = Dijkstra(maze, rows, cols, sx, sy, ex, ey);

	if (dist == -1) 
		printf("NO path found\n");
	else
		printf("Min path found using %d units\n", dist);
	return 0;
}

