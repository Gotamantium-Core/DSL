#include <stdio.h>
#include <stdlib.h>

// Directions: Up, Down, Left, Right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// Queue node for BFS
typedef struct QNode {
    int x, y;
    struct QNode* next;
} QNode;

// Dynamic queue
typedef struct Queue {
    QNode *front, *rear;
} Queue;

void initQueue(Queue* q) { q->front = q->rear = NULL; }
int isEmpty(Queue* q) { return q->front == NULL; }

void enqueue(Queue* q, int x, int y) {
    QNode* node = malloc(sizeof(QNode));
    node->x = x;
    node->y = y;
    node->next = NULL;
    if(q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }
    q->rear->next = node;
    q->rear = node;
}

QNode dequeue(Queue* q) {
    QNode node = {0,0,NULL};
    if(isEmpty(q)) return node;
    QNode* temp = q->front;
    node.x = temp->x;
    node.y = temp->y;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    free(temp);
    return node;
}

// Check if cell is valid and open
int isValid(int x, int y, int rows, int cols, char** maze, int** visited) {
    return (x >=0 && x < rows && y >=0 && y < cols && maze[x][y] == '0' && !visited[x][y]);
}

// BFS to find shortest path and reconstruct it
void bfs(char** maze, int rows, int cols, int sx, int sy, int ex, int ey) {
    int** visited = malloc(rows * sizeof(int*));
    int** distance = malloc(rows * sizeof(int*));
    int** parentX = malloc(rows * sizeof(int*));
    int** parentY = malloc(rows * sizeof(int*));
    for(int i=0;i<rows;i++){
        visited[i] = calloc(cols,sizeof(int));
        distance[i] = malloc(cols*sizeof(int));
        parentX[i] = malloc(cols*sizeof(int));
        parentY[i] = malloc(cols*sizeof(int));
        for(int j=0;j<cols;j++){
            distance[i][j] = -1;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
        }
    }

    Queue q;
    initQueue(&q);
    enqueue(&q, sx, sy);
    visited[sx][sy] = 1;
    distance[sx][sy] = 0;

    while(!isEmpty(&q)){
        QNode curr = dequeue(&q);

        if(curr.x == ex && curr.y == ey) break;

        for(int i=0;i<4;i++){
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if(isValid(nx, ny, rows, cols, maze, visited)){
                visited[nx][ny] = 1;
                distance[nx][ny] = distance[curr.x][curr.y] + 1;
                parentX[nx][ny] = curr.x;
                parentY[nx][ny] = curr.y;
                enqueue(&q, nx, ny);
            }
        }
    }

    if(distance[ex][ey] == -1){
        printf("No path found\n");
    } else {
        printf("Shortest distance (charge units) = %d\n", distance[ex][ey]);
        // Reconstruct path
        int cx = ex, cy = ey;
        while(!(cx == sx && cy == sy)){
            maze[cx][cy] = '*';
            int px = parentX[cx][cy];
            int py = parentY[cx][cy];
            cx = px; cy = py;
        }
        maze[sx][sy] = 'S';
        maze[ex][ey] = 'E';

        // Print maze
        printf("Maze with path:\n");
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++)
                printf("%c ", maze[i][j]);
            printf("\n");
        }
    }

    for(int i=0;i<rows;i++){
        free(visited[i]); free(distance[i]); free(parentX[i]); free(parentY[i]);
    }
    free(visited); free(distance); free(parentX); free(parentY);
}

int main(){
    // Predefined from the question
    int rows = 6, cols = 8;
    char* maze[] = {
        "00001000",
        "01100010",
        "00011010",
        "01011010",
        "01001000",
        "00010101"
    };
    
    // convert to 2D array (dynamic)
    char** m = malloc(rows*sizeof(char*));
    for(int i=0;i<rows;i++){
        m[i] = malloc(cols*sizeof(char));
        for(int j=0;j<cols;j++)
            m[i][j] = maze[i][j];
    }

    // Find shortest path and print (if exists)
    bfs(m, rows, cols, 0,1, 5,6); // start at (0,1), end at (5,6)

    for(int i=0;i<rows;i++) free(m[i]);
    free(m);
}
