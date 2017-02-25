/*************************************************************************
  > File Name: insertionSort.cpp
  > Author: ma6174
  > Mail: ma6174@163.com 
  > Created Time: Wed 22 Feb 2017 11:34:02 AM UTC
 ************************************************************************/

#include <cstdio>
#include <climits>
#include<iostream>

using namespace std;

void insertSort(int * arr, int n){
	int v = 0;
	for (int i = 1; i<n; i++){
		v = arr[i];
		int j = i - 1;
		for(; j >= 0; j--){
			if(arr[j] > v){
				arr[j+1] = arr[j];
			}
			else {
				break;
			}
		}
		arr[j+1] = v;
	}
}

void merge(int *arr, int b, int m, int e){
	int l_num = m - b;
	int r_num = e - m;
	int * l_arr = new int(l_num + 1);
	int * r_arr = new int(r_num + 1);
	for (int i = b; i < m; i++){
		l_arr[i - b] = arr[i];
	}
	l_arr[l_num] = INT_MAX;
	for(int i = m; i < e; i++){
		r_arr[i-m] = arr[i];
	}
	r_arr[r_num] = INT_MAX;

	int i = 0, j = 0;
	for(int k = b; k < e; k++){
		if (l_arr[i] <= r_arr[j]){
			arr[k] = l_arr[i++];
		}
		else {
			arr[k] = r_arr[j++];
		}
	}
}

void merge_sort(int *arr, int b, int e){
	if (b < e - 1){
		int p = b + (e - b)/2;
		merge_sort(arr, b, p);
		merge_sort(arr, p, e);
		merge(arr, b, p, e);
	}
}

int main(){
	/*
	while(scanf("%d", &n) == 1){
		int * arr = new int[n];
		for (int i = 0; i < n; i++){
			int v;
			scanf("%d", &v);
			arr[i] = v;
		}

	*/
	int arr[] = {5, 2, 4, 7, 1, 3, 2, 6};
	int n = sizeof(arr)/sizeof(arr[0]);
		cout << "Before sorted: " << endl;
		for (int i = 0; i < n; i++){
			cout << arr[i] << " ";
		}
		cout << endl;
		//insertSort(arr, n);
		merge_sort(arr, 0, sizeof(arr)/sizeof(arr[0]));
		cout << "After sorted: " << endl;
		for (int i = 0; i < n; i++){
			cout << arr[i] << " ";
		}
		cout << endl;
	//	delete [] arr;
//	}

}

