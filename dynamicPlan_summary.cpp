//
//  main.cpp
//  SourceCode_Algorithm
//
//  Created by FrankLiu on 2017/8/13.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#include <iostream>

using namespace std;


int solve(int idx, int *arr){
    if(idx < 0){
        return 0;
    }
    int r = max(arr[idx] + solve(idx - 2, arr), solve(idx - 1, arr));
    return r;
}
int solve_v1 (int idx, int *arr, int *res){
    if (idx < 0){
        return 0;
    }
    if(res[idx] > 0){
        return res[idx];
    }
    int r1 = arr[idx] + solve_v1(idx- 2, arr, res);
    int r2 = solve_v1(idx -1, arr, res);
    if(r1 > r2){
        res[idx] = r1;
    }
    else {
        res[idx] = r2;
    }
    return r1;
    
}

int sovle_v2(int n, int *arr){
    int * c = new int[n];
    for(int i = 0;i < n; i++){
        c[i] = 0;
    }
    c[0] = arr[0];
    c[1] = max(arr[1], c[0]);
    
    for(int i = 2; i < n; i++){
        c[i] = max(arr[i] + c[i-2], c[i-1]);
    }
    return c[n-1];
}

void run(int *arr, int n){
    int mv = solve(n-1, arr);
    cout << "solve : " << mv << endl;
    
    int *res = new int[n];
    for(int i = 0; i < n; i++){
        res[i] = -1;
    }
    mv = solve_v1(n-1, arr, res);
    cout << "solve_v1 " << mv << endl;
    
    mv = sovle_v2(n, arr);
    cout << "solve2 : " << mv << endl;
}

int main(){
    int arr[] = {1, 2, 3};
    run(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
