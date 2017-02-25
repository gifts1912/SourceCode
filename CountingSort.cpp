#include<iostream>

using namespace std;

void OutArray(int *arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void CountingSort(int *arr, int n) {
	//all elements in arr are nonnegative integer
	int max = arr[0];
	int * preSortArr = new int[n+1];
	preSortArr[0] = arr[0];
	for (int i = 1; i < n; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
		preSortArr[i] = arr[i];
	}
	int * auxiliaryArr = new int[max+1];
	for (int i = 0; i < max+1; i++) {
		auxiliaryArr[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		auxiliaryArr[arr[i]] += 1;
	}
	for (int i = 1; i < max + 1; i++) {
		auxiliaryArr[i] = auxiliaryArr[i - 1] + auxiliaryArr[i];
	}

	for (int i = n-1; i >= 0; i--) {
		arr[auxiliaryArr[preSortArr[i]] - 1] = preSortArr[i]; // as the smallist value at position 1. That is all sorted elements poterpone 1 position.
		auxiliaryArr[preSortArr[i]] --;
	}
	OutArray(arr, n);
	delete[] auxiliaryArr;
	delete[] preSortArr;

}

int main() {
	int arr[] = { 6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Before Counting Sort:" << endl;
	OutArray(arr, n);
	CountingSort(arr, n);
	cout << "After Counting Sort:" << endl;
	OutArray(arr, n);
	getchar();
	return 0;
}