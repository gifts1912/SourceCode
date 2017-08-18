#include <iostream>
#include <limits>


using namespace std;
void head_sort(int *arr, int n){
    int b = (n-2)/2;
    int max_idx = -1;
    int max_v = numeric_limits<int>::min();
    for(int i = b; i >= 0; i--){
        if (arr[2 * i + 2] < arr[2 * i + 1]){
            max_idx = 2 * i + 1;
            max_v = arr[2 * i + 1];
        }
        else {
            max_idx = 2 * i + 2;
            max_v = arr[2 * i + 2];
        }
        
        if (arr[i] < max_v){
            arr[max_idx] = arr[i];
            arr[i] = max_v;
        }
    }
    for(int i = 0; i < n; i++){
        cout << arr[i] << '\t';
    }
    cout << endl;
}

int main(){
    int arr[] = {2, 1, 5, 3, 4};
    head_sort(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
