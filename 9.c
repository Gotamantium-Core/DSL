#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node *next;
} Node;

Node* createNew(int, int);
void Insert(Node ** , int, int);
void Display(Node *);
Node* Multiply(Node *, Node *);

int main() {
    Node* p1 = NULL, *p2 = NULL;
    int m, n, coeff, exp;

    printf("Enter number of terms in polynomial 1: ");
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        printf("Enter term (coeff exp): ");
        scanf("%d %d", &coeff, &exp);
        Insert(&p1, coeff, exp);
    }

    printf("Enter number of terms in polynomial 2: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter term (coeff exp): ");
        scanf("%d %d", &coeff, &exp);
        Insert(&p2, coeff, exp);
    }

    Node* res = Multiply(p1, p2);
    printf("Result: ");
    Display(res);
    return 0;
}


void Insert(Node* *top, int coeff, int exp) {
    if (coeff == 0) return;
    Node* newNode = createNew(coeff, exp);
    if (*top == NULL || (*top)->exp < exp) {
        newNode->next = *top;
        *top = newNode;
        return;
    }
    
    Node* prev = NULL, *temp = *top;
    while (temp && temp->exp > exp) {
        prev = temp;
        temp = temp->next;
    }
    if (temp && temp->exp == exp) {
        temp->coeff += coeff;
        free(newNode);
        return;
    }
    newNode->next = temp;
    if (prev) prev->next = newNode;
    else *top = newNode;
}

Node* createNew(int coeff, int exp) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}
Node* Multiply(Node* Poly1, Node* Poly2) {
    Node* res = NULL;
    for (Node* i = Poly1; i; i = i->next)
    for (Node* j = Poly2; j; j = j->next)
    Insert(&res, i->coeff * j->coeff, i->exp + j->exp);
    return res;
}
void Display(Node* top) {
    Node* temp = top;
    while (temp) {
        printf("%dx^%d ", temp->coeff, temp->exp);
        temp = temp->next;
    }
    printf("\n");
}