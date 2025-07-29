/*
You have been hired for developing animation games by RoboGames Ltd. The game environ-
ment has multiple layers of objects as follows:
Layer 1: Static buildings
Layer 2: Moving vehicles
Layer 3: Animated characters
Each object has a position represented on a 2D grid. Since most positions are empty (no object),
sparse matrices are employed to represent updates from different layers of a virtual scene. The
individual matrices are added to compute the total transformation for the frame. The final
transformation matrix is transposed before sending to the GPU (Graphical Processing Unit) for
rendering. This is to match the column-major format expected by shaders. (Shaders are small
programs that run on a GPU to determine how objects and scenes are rendered on the screen).
Your job now is to input the updates from a scene and feed them to the shader.
*/
#include <stdio.h>

typedef struct {
    int row;
    int col;
    int val;
} Element;

void Tripletify(int arr[10][10], int m, int n, Element T[]) {
    T[0].row = m; T[0].col = n;
    int k=1;
    for (int i=0; i < m; i++) 
        for (int j=0; j < n; j++)
            if (arr[i][j] != 0) {
                T[k].val = arr[i][j];
                T[k].row = i;
                T[k].col = j;

                k++;
            }
    T[0].val = k-1;
}

void Add(Element T1[], Element T2[], Element res[]) {
    int m = T1[0].val;
    int n = T2[0].val;
    int i = 1, j = 1, k = 1;

    while (i <= m && j <= n) {
        if (T1[i].row < T2[j].row || 
           (T1[i].row == T2[j].row && T1[i].col < T2[j].col)) {
            res[k++] = T1[i++];
        } else if (T1[i].row > T2[j].row || 
                  (T1[i].row == T2[j].row && T1[i].col > T2[j].col)) {
            res[k++] = T2[j++];
        } else {
            int sum = T1[i].val + T2[j].val;
            if (sum) {
                res[k].row = T1[i].row;
                res[k].col = T1[i].col;
                res[k].val = sum;
                k++;
            }
            i++; j++;
        }
    }

    while (i <= m) res[k++] = T1[i++];
    while (j <= n) res[k++] = T2[j++];

    res[0].row = T1[0].row;
    res[0].col = T1[0].col;
    res[0].val = k - 1;
}

void Transpose(Element T[], Element transp[]) {
    transp[0] = T[0];
    for (int i=1; i <= T[0].val; i++) {
        transp[i] = T[i];
        
        // swap
        int temp = transp[i].col;
        transp[i].col = transp[i].row;
        transp[i].row = temp;
    }

    // sort it back 
    for (int i=1; i <= transp[0].val; i++) {
        for (int j=1; j < transp[0].val; j++) {
            if (transp[j].row > transp[j+1].row) {
                Element temp = transp[j];
                transp[j] = transp[j+1];
                transp[j+1] = temp;
            }
        }
    }
    // done!?
}

void printTriplet(Element T[]) {
    for (int i=0; i <= T[0].val; i++) 
        printf("(%d, %d, %d)\n", T[i].row, T[i].col, T[i].val);
    printf("\n\n");
}

int main() {
    int A[10][10] = {{0, 1, 2},{0, 0, 3},{4, 0, 0}}; // Layer 1
    int B[10][10] = {{5, 0, 6},{0, 7, 0},{0, 8, 0}}; // Layer 2
    int C[10][10] = {{9, 10, 0},{11, 0, 0},{0, 0,12}}; // Layer 3
    Element tA[20], tB[20], tC[20], temp[40], ttemp[60], tempT[60]; // all the triplet matrices
    int n=3; // size of all the matrices (can be changed)

    // Convert to triplet form
    Tripletify(A, n, n, tA);
    Tripletify(B, n, n, tB);
    Tripletify(C, n, n, tC);

    // Add them together
    Add(tA, tB, temp);
    Add(temp, tC, ttemp);

    // Take the transpose of the result
    Transpose(ttemp, tempT);

    printTriplet(tempT);
    return 0;
}
