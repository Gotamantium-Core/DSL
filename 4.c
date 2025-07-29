/*
Write a menu-driven program for the following operations:
(a) Convert an infix expression to a postfix expression.
(b) Evaluate the postfix expression.
*/

#include <stdio.h>
#include <ctype.h> // for the isdigit and isalnum functions;

// for evaluation
int evalStack[100];

// for conversion
char stack[100];
int top = -1, topEval = -1;


void ConvertToPostfix(char *, char *);
int precedence(char);
int rightAssociative(char);
int Evaluate(char *);
void resetStack(int st) {
    if (st == 0)
        top = -1;
    else if (st == 1)
        topEval = -1;
}
int empty() {
    return top == -1;
}
void push(char elem) {
    if (top < 99) { // if not full
        top++;
        stack[top] = elem;
    }
}
char pop() {
    if (top >= 0) // if not empty
        return stack[top--];
    return '\0';
}
char peek() {
    if (top >= 0) { // if not empty
        return stack[top];
    }
    return '\0';
}
void pushEval(int elem) {
    topEval++;
    evalStack[topEval] = elem;
}
int popEval() {
    return evalStack[topEval--];
}


int main() {
    int func;
    while (1) {
        printf("1. Convert infix to postfix \n2. Evaluate postifx \n0. Quit \nEnter function: ");
        scanf("%d", &func);

        if (0 == func) break;
        else if (func == 1) {
            char infix[50], postfix[50];
            printf("Enter infix expression: ");
            scanf("%s", infix);

            ConvertToPostfix(infix, postfix);
            printf("Equivalent postfix: %s\n", postfix);
        } else if (func == 2) {
            char exp[50];
            printf("Enter postfix expression: ");
            scanf("%s", exp);
            int val = Evaluate(exp);
            printf("Value of expression is: %d\n", val);
        } else {
            printf("Invalid function, try again\n\t->");
        }
    }
    return 0;
}


void ConvertToPostfix(char *in, char *out) {
    resetStack(0);
    int k=0;
    for (int i=0; in[i] != '\0'; i++) {
        char ch = in[i];
        if (isalnum(ch))
            out[k++] = ch;
        else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (!empty() && peek() != '(') {
                out[k++] = pop();
            }
            pop(); // remove the (
        } else {
            while (!empty() && 
                (precedence(ch) < precedence(peek())) ||
                (precedence(ch) == precedence(peek()) && !rightAssociative(ch)) &&
                peek() != '(') {
                    out[k++] = pop();
                }
            push(ch);
        }
    }
    while (!empty()) 
        out[k++] = pop();
    out[k] = '\0';
}

int Evaluate(char *exp) {
    resetStack(1);
    for (int i=0; exp[i] != '\0'; i++) {
        char ch = exp[i];
        if (isdigit(ch)) {
            pushEval(ch - '0'); // converting to int
        } else {
            int b = popEval();
            int a = popEval();
            int res;
            switch (ch) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                case '^':
                    res = 1;
                    for (int j = 0; j < b; j++) res *= a;
                    break;
                default:
                    printf("Invalid operator: %c\n", ch);
                    return -1;
            }
            pushEval(res);
        }
    }
    return popEval();
}

int precedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '/': case '*':
            return 2;
        case '+': case '-':
            return 1;
        default: return 0;
    }
}
int rightAssociative(char op) {
    return op == '^';
}
