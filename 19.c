#include <stdio.h>


void ReverseSort(int arr[], int n) { 
	for (int i=0; i < n-1; i++) {
		int swapped=0;
		for (int j=0; j < n-i-1; j++)
			if (arr[j] < arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				swapped=1;
			}
		if (!swapped) break;
	}
}

int main() {
	int n,k;

	printf("Enter length of array: ");
	scanf("%d", &n);
	int arr[n];
	for (int i=0; i < n; i++) scanf("%d", &arr[i]);

	printf("Enter maximum(k): ");
	scanf("%d", &k);

	if (k > n) {
		printf("Not enough events\n");
		return 0;
	}

	ReverseSort(arr, n);

	int res=0;
	for (int i=0; i < k; i++)
		res += arr[i];

	printf("You can earn a max of %d points.\n", res);
	return 0;
}
