#include <iostream>
#include <limits>

using namespace std;

void head_adjust(int *arr, int n){
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
    /*
    for(int i = 0; i < n; i++){
        cout << arr[i] << '\t';
    }
    cout << endl;
    */
}

void heap_sort(int *arr, int n){
    head_adjust(arr, n);
    for(int i = 0; i < n; i++){
        int v = arr[n-1-i];
        arr[n-1-i] = arr[0];
        arr[0] = v;
        head_adjust(arr, n - 1 - i);
    }
    for(int i = 0; i < n; i++){
        cout << arr[i] << '\t';
    }
    cout << endl;
}


#define V 5

using namespace std;

const int INIFINITE = numeric_limits<int>::max();

void allPairsShotestPathMatrixMul(int matrix[][V]){
    int L[V][V];
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            L[i][j] = matrix[i][j];
        }
    }
    
    for(int iter = 2; iter < V; iter ++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                for(int k = 0; k < V; k++){
                    if(L[i][k] != INIFINITE && matrix[k][j] != INIFINITE && L[i][j] > L[i][k] + matrix[k][j])
                        L[i][j] = L[i][k] + matrix[k][j];
                }
            }
        }
    }
    
    cout << "After n path the shorted path distance is :" << endl;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if (L[i][j] == INIFINITE) {
                cout << "INT" << '\t';
            }
            else
                cout << L[i][j] << '\t';
        }
        cout << endl;
    }
    
}

int main(){
    int matrix[V][V] = {
        {0, 3, 8, INIFINITE, -4},
        {INIFINITE, 0, INIFINITE, 1, 7},
        {INIFINITE, 4, 0, INIFINITE, INIFINITE},
        {2, INIFINITE, -5, 0, INIFINITE},
        {INIFINITE, INIFINITE, INIFINITE, 6, 0}
    };
    
    allPairsShotestPathMatrixMul(matrix);
    
    return 0;
}

/*
int main(){
    int arr[] = {2, 1, 5, 3, 4};
    heap_sort(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
*/
