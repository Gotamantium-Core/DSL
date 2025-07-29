#include <stdio.h>

typedef struct {
    int coeff;
    int exp;
} Term;

void Display(Term [], int);
int AddMod3(Term [], int, Term [], int, Term []);

int main()  {
    // Term m[7], k[7], c[14];
    // input them somehow i dont fucking know

    // sample inputs
    Term m[] = {{1, 6},{1, 2},{0, 2}};
    Term k[] = {{1, 5},{1, 2},{1, 0}};
    Term c[14];
    int n1 = sizeof(m) / sizeof(m[0]);
    int n2 = sizeof(k) / sizeof(k[0]);

    printf("Final polynomial: ");
    int n3 = AddMod3(m, n1, k, n2, c);
    Display(c, n3);
}

// downsides: will not be in sorted order
int AddMod3(Term m[], int n1, Term k[], int n2, Term c[]) {
    int temp=0, count=n1+n2, found;
    for (int i=0; i < n1; i++)
        c[temp++] = m[i];
    
    for (int i=0; i < n2; i++) {
        found = 0;
        for (int j=0; j < temp; j++)
            if (c[j].exp == k[i].exp) {
                c[j].coeff = (c[j].coeff + k[i].coeff) % 3; // mod 3 addition
                count--;
                found = 1;
                break;
            }
        if (!found && k[i].coeff != 0)
            c[temp++] = k[i];
    }
    return temp;
}

void SortByExp(Term c[], int n) {
    int swapped;
    for (int i=0; i < n; i++) {
        swapped = 0;
        for (int j=0; j < n-1; j++)
            if (c[j].exp < c[j+1].exp) {
                Term temp = c[j];
                c[j] = c[j+1];
                c[j+1] = temp;
                swapped=1;
            }
        if (!swapped)
            break;
    } 
}
void Input(Term c[], int n) {
    printf("Enter terms: ");
    int i=0;
    while (n) {
        scanf("%d %d", &c[i].coeff, &c[i].exp);
        if ((c[i].coeff > 3 || c[i].coeff < 0) || (c[i].exp > 6 || c[i].exp < 0)) {
            printf("Invalid inputs. Try again.\n\t");
            continue;
        }
        n--, i++;
    }
}
void Display(Term c[], int n) {
    for (int i=0; i < n; i++) { // NOTE: the order is significant
        if (c[i].coeff == 0) {
            printf("");
        } else if (c[i].exp == 0) {
            printf("%d ", c[i].coeff);
        } else if (c[i].exp == 1) {
            printf("%dx ", c[i].coeff);
        } else if (c[i].coeff == 1) {
            printf("x^%d ", c[i].exp);
        } else {     
            printf("%dx^%d ", c[i].coeff, c[i].exp);
        }
        if ((i != n-1) && (c[i].coeff)) printf("+ ");
    }
    printf("\n");
}