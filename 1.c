#include <stdio.h>

int sum(int [], int);
int max(int [], int);
int isValid(int [], int, int, int);
void partition(int [], int, int, int);

int main() {
    int s, n;
    printf("Enter number of students: ");
    scanf("%d", &s);

    printf("Enter number of books: ");
    scanf("%d", &n);
    
    int Students[s], pages[n];

    printf("Enter number of pages in each book: ");
    for (int i=0; i < n; i++) 
        scanf("%d", &pages[i]);
        
    int l=sum(pages, n);
    int r=max(pages, n);
    int res = r;
    while (l <= r) {
        int mid = (l+r)/2;

        if (isValid(pages, s, n, mid)) {
            res = mid;
            r = mid-1;
        } else {
            l = mid+1;
        }
    }

    partition(pages, n, s, res);
    return 0;
}


int sum(int arr[], int n) {
    int sum=0;
    for (int i=0; i < n; i++)
        sum += arr[i];
    return sum;
}

int max(int arr[], int n) {
    int max = arr[0];
    for (int i=0; i < n; i++)
        if (max < arr[i])
            max = arr[i];
    return max;
}

int isValid(int pages[], int s, int n, int maxPages) {
    int StudentCount=1, currSum = 0;
    for (int i=0; i < n; i++) {
        if (pages[i] > maxPages)
            return 0;

        if (currSum + pages[i] > maxPages) {
            StudentCount++;
            currSum = pages[i];
            if (StudentCount > s)
                return 0;
        } else {
            currSum += pages[i];
        }
    }
    return 1; 
}

void partition(int pages[], int n, int s, int maxPages) {
    int sum = 0, student = 1;
    printf("Student %d: ", student);

    for (int i = 0; i < n; i++) {
        if (sum + pages[i] > maxPages) {
            printf(" | %d pages\n", sum);
            
            student++;
            printf("Student %d: ", student);
            sum = 0;
        }
        printf("%d ", pages[i]);
        sum += pages[i];
    }

    printf(" | %d pages\n", sum);
}

