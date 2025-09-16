#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Leaf {
    char op;                 // operator or operand
    struct Leaf *left;
    struct Leaf *right;
} Leaf;

typedef struct OpStack {
    char op;
    struct OpStack *next;
} OpStack;

typedef struct NodeStack {
    Leaf *treeNode;
    struct NodeStack *next;
} NodeStack;
// opStack = chars, nodeStack = nodes
// Leaf = tree node

char top(OpStack* head) {
    if (head == NULL) return '\0';
    return head->op;
}
char empty(OpStack* head) {
    return head == NULL;
}
int precedence(char op) {
    if (op == '^') return 3;
    else if (op == '/' || op == '*') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0;
}
// Node operations
// Operator stack push/pop
void pushOp(OpStack **top, char op) {
    OpStack *new = malloc(sizeof(OpStack));
    new->op = op;
    new->next = *top;
    *top = new;
}

char popOp(OpStack **top) {
    if (*top == NULL) return '\0'; // empty
    OpStack *temp = *top;
    char c = temp->op;
    *top = temp->next;
    free(temp);
    return c;
}

// Node stack push/pop
void pushNode(NodeStack **top, Leaf *node) {
    NodeStack *new = malloc(sizeof(NodeStack));
    new->treeNode = node;
    new->next = *top;
    *top = new;
}

Leaf* popNode(NodeStack **top) {
    if (*top == NULL) return NULL;
    NodeStack *temp = *top;
    Leaf *node = temp->treeNode;
    *top = temp->next;
    free(temp);
    return node;
}

void BuildSubtree(OpStack* *opStack, NodeStack* *nodeStack) {
    char op = popOp(opStack);
    Leaf* rightChild = popNode(nodeStack); 
    Leaf* leftChild = popNode(nodeStack);
    
    Leaf* root = malloc(sizeof(Leaf));
    root->op = op;
    root->left = leftChild;
    root->right = rightChild;
    
    pushNode(nodeStack, root);
}
Leaf* ConstructExpressionTree(char* expression) {
    OpStack *opStack = NULL;
    NodeStack *nodeStack = NULL;

    for (int i=0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (isalnum(ch)) {
            Leaf *newLeaf = malloc(sizeof(Leaf));
            newLeaf->op = ch;
            newLeaf->left = newLeaf->right = NULL;
            pushNode(&nodeStack, newLeaf);
        } 
        else if (ch == '(') {
            pushOp(&opStack, ch);
        } 
        else if (ch == ')') {
            while (top(opStack) != '(')
                BuildSubtree(&opStack, &nodeStack);
            popOp(&opStack); // discard '('
        } 
        else { // operator
            while (!empty(opStack) && top(opStack)!='(' && 
                   precedence(top(opStack)) >= precedence(ch))
                BuildSubtree(&opStack, &nodeStack);
            pushOp(&opStack, ch);
        }
    }

    while (!empty(opStack))
        BuildSubtree(&opStack, &nodeStack);

    return popNode(&nodeStack); // root of tree
}

void preorder(Leaf *root) {
    if (root == NULL) return;
    printf("%c", root->op);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Leaf *root) {
    if (root == NULL) return;
    if (root->left || root->right) printf("("); // for clarity
    inorder(root->left);
    printf("%c", root->op);
    inorder(root->right);
    if (root->left || root->right) printf(")");
}

void postorder(Leaf *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->op);
}

int main() {
    char expr[] = "(A+B*C)-((D*E+F)/G)";
    Leaf *root = ConstructExpressionTree(expr);

    printf("Inorder  (infix):   ");
    inorder(root);
    printf("\n");

    printf("Preorder (prefix):  ");
    preorder(root);
    printf("\n");

    printf("Postorder(postfix): ");
    postorder(root);
    printf("\n");

    return 0;
}


