#include <iostream>
#include <cstdio>
#include <climits>
#include <random>

using namespace std;

void MinMaxGet(int *arr, int n) {
	if (n < 1) {
		cout << "Empty array!" << endl;
		return;
	}
	int min, max, b;
	if (n % 2 == 0) {
		if (arr[0] > arr[1]) {
			min = arr[1];
			max = arr[0];
		}
		else {
			min = arr[0];
			max = arr[1];
		}
		b = 2;
	}
	else {
		min = max = arr[0];
		b = 1;
	}
	for (int i = b; i < n; i += 2) {
		if (arr[i] > arr[i + 1]) {
			if (arr[i + 1] < min) {
				min = arr[i + 1];
			}
			if (arr[i] > max) {
				max = arr[i];
			}
		}
		else {
			if (arr[i] < min) {
				min = arr[i];
			}
			if (arr[i + 1] > max) {
				max = arr[i + 1];
			}
		}
	}
	cout << "max= " << max << '\t' << "min= " << min << endl;
	return;
}

int RandomPartition(int *arr, int b, int e) {
	default_random_engine generator;
	uniform_int_distribution<int> distribution(b, e - 1);
	int r = distribution(generator);
	int v = arr[e - 1];
	arr[e - 1] = arr[r];
	arr[r] = v;
	v = arr[e - 1];
	int i = b, j = e-2;
	while (true) {
		while (arr[i] <= v) {
			i++;
		}
		while (j >= 0 && arr[j] > v) {
			j--;
		}
		if (i < j) {
			int t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
		else {
			break;
		}
	}
	arr[e - 1] = arr[j+1];
	arr[j + 1] = v;
	return j + 1;
}

int GetKthMin(int *arr, int b, int e, int k) {
	if (b == e - 1) {
		if (k == 1)
			return arr[b];
		else
			return -1;
	}
	int p = RandomPartition(arr, b, e);
	int len = p - b;
	if (k == len+1) {
		return arr[p];
	}
	else if (k < len+1) {
		GetKthMin(arr, b, p, k);
	}
	else {
		GetKthMin(arr, p+1, e, k - len-1);
	}
}
/*
int main() {
	int arr[] = { 1, 10, 2, 3, 5, 20};
	//MinMaxGet(arr, sizeof(arr) / sizeof(arr[0]));
	int i = 6;
	int v = GetKthMin(arr, 0, sizeof(arr)/sizeof(arr[0]), i);
	cout << v << endl;
	getchar();
	return 0;
}*/