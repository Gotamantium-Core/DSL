#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void deepCopy(int arr[], int n, int res[]) {
	for (int i=0; i < n; i++)
		res[i] = arr[i];
}
void disp(int arr[], int n) {
	for (int i=0; i < n; i++) printf("%d ", arr[i]); printf("\n");
}

int BubbleSort(int arr[], int n) {
	int steps=0;
	for (int i=0; i < n-1; i++) {
		for (int j=0; j < n-i-1; j++)
			if (arr[j] < arr[j+1])
				swap(&arr[j], &arr[j+1]);
		steps += 3;
	}
	return steps;
}

int InsertionSort(int arr[], int n) {
	int steps=0;
	for (int i=1; i < n; i++) {
		int key = arr[i];
		int j = i-1;
		
		while (j >= 0 && arr[j] < key) {
			arr[j+1] = arr[j];
			j--;
			steps++;
		}
		arr[j+1] = key;
		steps++;
	}
}

void merge(int arr[], int l, int m, int r, int* steps) {
	int n1 = m + 1 - l;
	int n2 = r - m;
	int la[100], ra[100];
	for (int i=0; i < n1; i++) la[i] = arr[l + i];
	for (int i=0; i < n2; i++) ra[i] = arr[m+1 + i];
	int i=0, j=0, k=l;
	while (i < n1 && j < n2) {
		if (la[i] > ra[j])
			arr[k++] = la[i++];
		else 
			arr[k++] = ra[j++];
		(*steps)++;
	}
	while (i < n1) {
		arr[k++] = la[i++];
		(*steps)++;
	}
	while (j < n2) {
		arr[k++] = ra[j++];
		(*steps)++;
	}
}
void MergeSort(int arr[], int left, int right, int* steps) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid, steps);
		MergeSort(arr, mid+1, right, steps);
		merge(arr, left, mid, right, steps);
	}
}

int partition(int arr[], int low, int high, int* steps) {
	int pivot = arr[high];
	int pi = low;
	for (int i=low; i < high; i++)
		if (arr[i] > pivot) {
			swap(&arr[i], &arr[pi]);
			pi++;
			(*steps)++;
		}
	swap(&arr[high], &arr[pi]);
	(*steps)++;
	return pi;
}
void Quicksort(int arr[], int low, int high, int* steps) {
	if (low < high) {
		int pi = partition(arr, low, high, steps);
		Quicksort(arr, low, pi-1, steps);
		Quicksort(arr, pi+1, high, steps);
	}
}

int main() {
	FILE* fp = fopen("data.txt", "r");
	int n=0, arr[100];
	while (fscanf(fp, "%d", &arr[n]) == 1) n++;
	printf("Original: ");
	disp(arr, n);

	int barr[n], iarr[n], marr[n], qarr[n];
	deepCopy(arr, n, barr); deepCopy(arr, n, iarr); 
	deepCopy(arr, n, marr); deepCopy(arr, n, qarr);

	int bs=0, ss=0, is=0, ms=0, qs=0, rs=0;
	bs = BubbleSort(barr, n);
	is = InsertionSort(iarr, n);
	MergeSort(marr, 0, n-1, &ms);
	Quicksort(qarr, 0, n-1, &qs);

	int func;
	while (1) {
		printf("1. Bubble Sort\n2. Insertion Sort\n3. Merge Sort\n4. Quicksort\n0. Quit\n");
		printf("Enter function: ");
		scanf("%d", &func);

		if (0 == func) break;
		else if (1 == func) {
			printf("Steps: %d\n", bs);
			disp(barr, n);
		} else if (2 == func) {
			printf("Steps: %d\n", is);
			disp(iarr, n);
		} else if (3 == func) {
			printf("Steps: %d\n", ms);
			disp(marr, n);
		} else if (4 == func) {
			printf("Steps: %d\n", qs);
			disp(qarr, n);
		}
	}
	return 0;
}
