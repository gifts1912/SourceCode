//
//  main.cpp
//  SourceCode_Algorithm
//
//  Created by FrankLiu on 2017/8/13.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>

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

int fib(int n){
    if (n < 2){
        return 1;
    }
    else {
        return fib(n-1) + fib(n-2);
    }
}

int fib_v2(int n, int *res){
    if (n < 0) {
        return 0;
    }
    else if(n < 2){
        return 1;
    }
    
    if(res[n] != -1){
        return res[n];
    }
    
    res[n] = fib_v2(n-1, res) + fib_v2(n-2, res);
    return res[n];
}

int fib_v3(int n){
    int *res = new int[n+1];
    res[0] = res[1] = 1;
    
    for(int i = 2; i <= n; i++){
        res[i] = res[i-1] + res[i-2];
    }
    return res[n];
}

void runFib(int n){
    int *res = new int[n+1];
    for(int i = 0; i < n+1; i++){
        res[i] = -1;
    }
    res[0] = res[1] = 1;
    int r = fib_v2(n, res);
    cout << "fib_v2(" << n << ") is : " << r << endl;
    
    
    r = fib_v3(n);
    cout << "fib_v3(" << n << ") is :" << r << endl;
}


int moveForward(int idx_x, int idx_y, int **res){
    if(idx_x < 0 || idx_y < 0){
        return 0;
    }
    if(idx_x == 0 || idx_y == 0){
        return 1;
    }
    if(res[idx_x][idx_y] != -1){
        return res[idx_x][idx_y];
    }
    res[idx_x][idx_y] = moveForward(idx_x -1, idx_y, res) + moveForward(idx_x, idx_y -1, res);
    return res[idx_x][idx_y];
}

int moveForwardv2(int x, int y){
    int ** res = (int **) malloc((x+1) * sizeof(int *));
    for(int i = 0; i <= x; i++){
        res[i] = new int[y+1];
        if(i == 0){
            fill(res[i], res[i] + y + 1, 1);
        }
        else {
            fill(res[i], res[i] + y + 1, -1);
            res[i][0] = 1;
        }
        
    }
    
    
    for(int i = 1; i <= x; i++){
        for(int j = 1; j <= y; j++){
            res[i][j] = res[i-1][j] + res[i][j-1];
        }
    }
    
    return res[x][y];
}

int bag01(int idx, int W, int *v, int *w){
    if(W <= 0){
        return 0;
    }
    if(idx < 0){
        return 0;
    }
    if(w[idx] > W){
        return bag01(idx-1, W, v, w);
        
    }
    else {
        return max(bag01(idx -1, W - w[idx],  v, w) + v[idx], bag01(idx-1, W, v, w));
    }
    
}


int bag01v2(int idx, int s, int *v, int *w){
    if(s <= 0){
        return 0;
    }
    if(idx < 0){
        return 0;
    }
    int **res = (int**) malloc(sizeof(int *)  * (idx+1));
    for(int i = 0; i < idx + 1; i++){
        res[i] = (int *) malloc(sizeof(int) * (s + 1));
        fill(res[i], res[i] + s + 1, -1);
    }
    
    if(res[idx][s] != -1){
        return res[idx][s];
    }
    
    if(s >= w[idx])
        res[idx][s] = max(bag01v2(idx -1, s-w[idx], v, w) + v[idx], bag01v2(idx-1, s, v, w));
    else
        res[idx][s] = bag01v2(idx-1, s, v, w);
    
    return res[idx][s];
}


int bag01v3(int idx, int s, int *v, int *w){
    int **res = (int **)malloc((idx + 1) * sizeof(int *));
    for(int i = 0; i <= idx; i++){
        res[i] = new int[s+1];
        fill(res[i], res[i] + s + 1, -1);
    }
    
    for(int i = 0; i <= s; i++){
        if(i < w[0])
            res[0][i] = 0;
        else
            res[0][i] = v[0];
    }

    for(int i = 1; i <= idx; i++){
        res[i][0] = 0;
        for(int j = 1; j <= s; j++){
            res[i][j] = res[i-1][j];
            if(w[i] <= j){
                res[i][j] = max(res[i][j], res[i-1][j-w[i]] + v[i]);
            }
        }
    }
    
    return res[idx][s];
}

int bag01v4(int idx, int s, int *v, int *w){
    int **res = (int **)malloc((2) * sizeof(int *));
    for(int i = 0; i <= 1; i++){
        res[i] = new int[s+1];
        fill(res[i], res[i] + s + 1, -1);
    }
    
    for(int i = 0; i <= s; i++){
        if(i < w[0])
            res[0][i] = 0;
        else
            res[0][i] = v[0];
    }
    
    for(int i = 1; i <= idx; i++){
        res[i%2][0] = 0;
        for(int j = 1; j <= s; j++){
            res[i%2][j] = res[(i-1)%2][j];
            if(w[i] <= j){
                res[i%2][j] = max(res[i%2][j], res[(i-1)%2][j-w[i]] + v[i]);
            }
        }
    }
    
    return res[idx %2][s];
}



void run_bag01(){
    int v[] = {60, 100, 120};
    int w[] = {10, 20, 30};
    int  W = 50;
    int n = sizeof(v)/sizeof(v[0]);
    cout << "bag01 result " << bag01(n, W, v, w) << endl;
    cout << "bag02 result " << bag01v2(n, W, v, w) << endl;
    cout << "bag03 result " << bag01v3(n, W, v, w) << endl;
    cout << "bag04 result " << bag01v4(n, W, v, w) << endl;
    
}
void runmf(int x, int y){
    int **res = (int **) malloc(sizeof(int *) * x);
    for(int i = 0; i < x; i++){
        res[i] = new int[y];
        fill(res[i], res[i] + y, -1);
    }
    
    int r ;
    
    r = moveForward(x-1, y-1, res);
    cout << "v1 move forward path number is : " << r << endl;
    
    
    r = moveForwardv2(x-1, y-1);
    cout << "v2 move forward path number is : " << r << endl;

    
}

const int INFI = numeric_limits<int>::max();

int coinsCom(int n, int *arr, int t){
    if(t < 0){
        return INFI;
    }
    if(t == 0){
        return 0;
    }
    int r = INFI;
    for(int i = 0; i < n; i++){
        int c = coinsCom(n, arr, t - arr[i]);
        if(c != INFI){
            r = min(r, c + 1);
        }
    }
    return r;
}

int coinsComv2(int n, int *arr, int t, int *res){
    if(t == 0){
        return 0;
    }
    if(t < 0){
        return INFI;
    }
    if(res[t] != INFI){
        return res[t];
    }
    
    res[t] = INFI;
    for(int i = 0; i < n; i++){
        int c = coinsComv2(n, arr, t-arr[i], res);
        if (c != INFI){
            res[t] = min(res[t], c  + 1);
        }
    }
    return res[t];
}


int coinsComv3(int n, int *arr, int t){
    int *res = new int[t+1];
    fill(res, res+ t + 1, INFI);
    res[0] = 0;
    
    for(int j = 1; j <=  t; j++){
        for(int i = 0; i < n; i++){
            if(j >= arr[i]){
                int c = res[j-arr[i]];
                if(c != INFI){
                    res[j] = min(c + 1, res[j]);
                }
            }
        }
    }
    
    return res[t];
}

int coinsComv4(int idx, int *arr, int t){
    if(idx < 0){
        return INFI;
    }
    if(t < 0){
        return INFI;
    }
    if(t == 0){
        return 0;
    }
    int a = coinsComv4(idx, arr, t-arr[idx]);
    if(a != INFI){
        return min(a + 1, coinsComv4(idx-1, arr, t));
    }
    return coinsComv4(idx-1, arr, t);
}

int coinsComv5(int idx, int *arr, int t, int **res){
    if(idx < 0){
        return INFI;
    }
    if(t < 0){
        return INFI;
    }
    if(t == 0){
        return 0;
    }
    if(res[idx][t] != INFI){
        return res[idx][t];
    }
    
    int a = coinsComv5(idx, arr, t-arr[idx], res);
    if(a != INFI){
        res[idx][t] = min(a + 1, coinsComv5(idx-1, arr, t, res));
    }
    else {
        res[idx][t] = coinsComv5(idx-1, arr, t, res);
    }
    return res[idx][t];
}

int coinsComv6(int idx, int *arr, int t){
    if(t == 0){
        return 0;
    }
    int **res = (int **)malloc((idx + 1) * sizeof(int *));
    for(int i = 0; i <= idx; i++){
        res[i] = (int *) malloc(sizeof(int) * (t+1));
        fill(res[i], res[i] + t +  1, INFI);
    }
    
    res[0][0] = 0;
    for(int i = 0; i <= idx; i++){
        for(int j = 0; j <= t; j++){
            if(j >= arr[i]){
                int m = res[i][j-arr[i]];
                if(m != INFI){
                    m++;
                    res[i][j] = m;
                }
            }
            if(i >= 1){
                res[i][j] = min(res[i][j], res[i-1][j]);
            }
        }
    }
    return res[idx][t];
}

void run_coinsCom(int n, int *arr, int t){
    int *res = new int[t+1];
    fill(res, res + t + 1, INFI);
    int r = coinsCom(n, arr, t);
    cout << "coinsCom : " << r << endl;
    if(r == INFI){
        cout << "-1" << endl;
    }
    
    r = coinsComv2(n, arr, t, res);
    cout << "coinsComv2 : " << r << endl;
    if(r == INFI){
        cout << "-1" << endl;
    }
    
    r = coinsComv3(n, arr, t);
    cout << "coinsComv3 : " << r << endl;
    if(r == INFI){
        cout << "-1" << endl;
    }
    
    r = coinsComv4(n-1, arr, t);
    cout << "coinsComv4 : " << r << endl;
    if(r == INFI){
        cout << "-1" << endl;
    }
    
    int ** r4 = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        r4[i] = new int[t+1];
        fill(r4[i], r4[i] + t + 1, INFI);
    }
    r4[0][0] = 0;
    
    r = coinsComv5(n-1, arr, t, r4);
    cout << "coinsComv5 : " << r << endl;
    if(r == INFI){
        cout << "-1" << endl;
    }
    
    
    r = coinsComv6(n-1, arr, t);
    cout << "coinsComv6 : " << r << endl;
    if(r == INFI){
        cout << "-1" << endl;
    }
    
    delete [] res;
    for(int i = 0; i < n; i++){
        delete [] r4[i];
    }
    delete [] r4;
}

int maxComSubStr(char *a, char *b, int i, int j){
    if (i < 0 || j < 0){
        return 0;
    }
    
    int l = 0;
    if(a[i] == b[j])
    {
        l = 1 + maxComSubStr(a, b, i-1, j-1);
    }
    else {
        l = max(l, maxComSubStr(a, b, i-1, j-1));
    }
    l = max(l, maxComSubStr(a, b, i-1, j));
    l = max(l, maxComSubStr(a, b, i, j-1));
    return l;
}

int maxComSubStrV2(char *a, char *b, int i, int j, int **res){
    if (i < 0 || j < 0){
        return 0;
    }
    
    if(res[i][j] > 0) {
        return res[i][j];
    }
    
    int l = 0;
    if(a[i] == b[j])
    {
        l = 1 + maxComSubStr(a, b, i-1, j-1);
    }
    else {
        l = max(l, maxComSubStr(a, b, i-1, j-1));
    }
    l = max(l, maxComSubStr(a, b, i-1, j));
    l = max(l, maxComSubStr(a, b, i, j-1));
    res[i][j] = l;
    return l;
    
}

int maxComSubStrV3(char *a, char *b, int ea, int eb){
    int **res = (int **) malloc(sizeof(int*) * (ea + 1));
    for(int i = 0; i <= ea; i++){
        res[i] = (int *) malloc(sizeof(int) * (eb + 1));
        fill(res[i], res[i] + eb + 1, -1);
    }

    for(int i = 0; i <= ea; i++){
        res[i][0] = 0;
    }
    for(int j = 0; j <= eb; j++){
        res[0][j] = 0;
    }
    
    
    for(int i = 1; i <= ea; i++){
        for(int j = 1; j <= eb; j++){
            int l = -1;
            if(a[i] == b[j]){
                l = max(l, 1 + res[i-1][j-1]);
            }
            l = max(l, res[i-1][j]);
            l = max(l, res[i][j-1]);
            res[i][j] = l;
        }
    }
    
    return res[ea][eb];
    
}

void run_maxComSubStr(char * sa, char *sb){
    int la = strlen(sa), lb = strlen(sb);
    
    int l = maxComSubStr(sa, sb, la-1, lb-1);
    cout << "maxComSubStr : " << l << endl;
    
    int **res = (int **) malloc(sizeof(int*) * la);
    for(int i = 0; i < la; i++){
        res[i] = (int *) malloc(sizeof(int) * lb);
        fill(res[i], res[i] + lb, -1);
    }
    
    l = maxComSubStrV2(sa, sb, la-1, lb-1, res);
    cout << "maxComSubStrV2 : " << l << endl;
    
    l = maxComSubStrV3(sa, sb, la, lb);
    cout << "maxComSubStrV3 : " << l << endl;

    
}
int main(){
    /*
    int arr[] = {1, 2, 3};
    run(arr, sizeof(arr)/sizeof(arr[0]));
    */
            
    //runFib(3);
    
    //runmf(3, 5);
    
    //run_bag01();
    /*
    int arr[] = {1, 2, 5};
    int t = 11;
    int n = sizeof(arr)/sizeof(arr[0]);
    run_coinsCom(n, arr, t);
    */
    

    char *X = "GeeksforGeeks";
    char *y = "GeeksQuiz";
   
    run_maxComSubStr(X, y);
    
    return 0;
}

