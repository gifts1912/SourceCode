#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <vector>

using namespace std;


class Solution {
public:
	string removeKdigits(string num, int k) {
		int len = num.size();
		if (len == 0 || k == 0) {
			return "";
		}
		int i = 0;
		stack<char> s;
		char c = num[i++];
		s.push(c);
		while (k > 0 && i < len) {
				c = num[i];
				if (!s.empty()) {
					if (c < s.top()) {
						s.pop();
						k--;
					}
					s.push(c);
				}
				i++;
		}
		if (k == 0) {
			while(i < len)
				s.push(num[i++]);
		}
		else{
			while (k > 0 && !s.empty()) {
				s.pop();
				k--;
			}
			if (s.empty() && k > 0) {
				return "";
			}
		}
		
		string res = "";
		while (!s.empty()) {
			res = s.top() + res;
			s.pop();
		}
		size_t pos = res.find_first_not_of('0', 0);
		if(pos != string::npos)
			res = res.substr(pos);
		return res;
	}

	int maxSubStr(vector<int> &vec) {
		int sum = 0, maxSum = numeric_limits<int>::min();
		vector<int>::iterator b = vec.begin(), e = vec.begin(), mb = vec.begin();
		for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
			if (sum < 0) {
				sum = *iter;
				b = iter;
			}
			else {
				sum += *iter;
			}
			if (sum > maxSum) {
				mb = b;
				e = iter;
				maxSum = sum;
			}
		}
		while (mb <= e) {
			cout << *mb << '\t';
			mb++;
		}
		return maxSum;
	}
};

int main() {
	Solution s;
	string num = "1432219";
	int k = 3;
	//num = "10200";
	//k = 1;
	cout << s.removeKdigits(num, k) << endl;


	int arr[] = { -2,1,-3,4,-1,2,1,-5,4 };
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	int res = s.maxSubStr(vec);
	cout << res << endl;
	getchar();
	return 0;
}

//
//  greedy_maxValueIncome_121.cpp
//  SourceCode_Algorithm
//
//  Created by FrankLiu on 2017/9/2.
//  Copyright © 2017年 FrankLiu. All rights reserved.
//

#include "greedy_maxValueIncome_121.hpp"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;


int maxStockIncome(int *arr, int idx){
    int min_value = numeric_limits<int>::max();
    int max_income = numeric_limits<int>::min();
    
    for(int i = 0; i < idx; i++){
        if (arr[i] < min_value){
            min_value = arr[i];
        }
        if(arr[i+1] - min_value > max_income){
            max_income = arr[i+1] - min_value;
        }
    }
    return max_income;
}

int maxStockIncomeManyTimes(int *arr,  int idx, int *visited){
    //LT122;
    if(idx <= 0){
        return 0;
    }
    if(visited[idx] > 0){
        return visited[idx];
    }
    
    int m = numeric_limits<int>::min();
    for(int k = 0; k < idx; k++){
        m = max(m, arr[idx] - arr[k] + maxStockIncomeManyTimes(arr, k-1, visited));
    }
    m = max(m, maxStockIncomeManyTimes(arr, idx-1, visited));
    visited[idx] = m;
    return m;
}

int maxStockIncomeManayTimes_v2_lt122(int *arr, int idx){
    int s = 0;
    for(int i = 1; i <= idx; i++){
        if(arr[i] - arr[i-1] > 0){
            s += arr[i] - arr[i-1];
        }
    }
    return s;
}
bool jump_55(int *arr, int idx, int n){
    if(idx >= n){
        return false;
    }
    if(idx == n-1){
        return true;
    }
    bool s = false;
    int m = arr[idx];
    for(int i = 1; i <= m; i++){
        if( idx + i < n){
            s = jump_55(arr, idx+i, n);
            if(s){
                return s;
            }
        }
    }
    return s;
}

bool jump_55_v2(int *arr, int idx, int n, int *visited){
    if(idx >= n){
        return false;
    }
    if(idx == n-1){
        return true;
    }
    if(visited[idx] != -1){
        return visited[idx];
    }
    
    bool s = false;
    int m = arr[idx];
    for(int i = m; i >= 1; i--){
        if( idx + i < n){
            s = jump_55(arr, idx+i, n);
            if(s){
                return s;
            }
        }
    }
   
    visited[idx] = s;
    return s;
}

bool jump_55_v3(int *arr, int idx){
    vector<int> reach(idx+1);
    fill(reach.begin(), reach.end(), -1);
    reach[idx] = 1;
    for(int i = idx - 1; i >= 0; i--){
        int e = min(i + arr[i], idx);
        bool flag = false;
        for(int k = e; k > i; k--){
            if(reach[k] == 1){
                flag = true;
                break;
            }
        }
        reach[i] = flag;
    }
    return reach[0];
}

bool jump_55_v4(int *arr, int idx){
    int lr = idx;
    for(int i = idx-1; i >= 0; i--){
        if(arr[i] + i >= lr){
            lr = i;
        }
    }
    return lr == 0;
}


int knapsack(int *v, int *w, int W, int idx){
    if (idx < 0 || W <= 0){
        return 0;
    }
    int m;
    
    if(W - w[idx] >= 0){
        m = max(knapsack(v, w, W, idx - 1), knapsack(v, w, W - w[idx], idx-1) + v[idx]);
    }
    else {
        m = knapsack(v, w, W, idx-1);
    }
    return m;
}


int knapsack_v2(int *v, int *w, int W, int idx, vector< vector<int> > &visited){
    if (idx < 0 || W <= 0){
        return 0;
    }
    if(visited[idx][W] != -1){
        return visited[idx][W];
    }
    
    int m;
    
    if(W - w[idx] >= 0){
        m = max(knapsack_v2(v, w, W, idx - 1, visited), knapsack_v2(v, w, W - w[idx], idx-1, visited) + v[idx]);
    }
    else {
        m = knapsack_v2(v, w, W, idx-1, visited);
    }
    visited[idx][W] = m;
    
    return m;
}

int knapsack_v3(int *v, int *w, int W, int idx){
    vector<vector<int> > vec(idx+1);
    for(int i = 0; i <= idx; i++){
        vec[i] = vector<int>(W+1);
        fill(vec[i].begin(), vec[i].end(), -1);
    }
    vec[0][0] = 0;
    
    for(int i = 0; i <= idx; i++){
        for (int j = 0; j <= W; j++){
            if (i == 0 || j == 0){
                vec[i][j] = 0;
            }
            else if(j >= w[i]){
                vec[i][j] = max(vec[i-1][j-w[i]] + v[i], vec[i-1][j]);
            }
            else {
                vec[i][j] = vec[i-1][j];
            }
        }
    }
    
    return vec[idx][W];
}



void run(){
    
    // max income of sell or buy share
    /*
    int arr[] = {7, 1, 5, 3, 6, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    int *visited = new int[sizeof(arr)/sizeof(arr[0])];
    fill(visited, visited + n, -1);
    int v = maxStockIncomeManyTimes(arr, n-1, visited);
    v = maxStockIncomeManayTimes_v2_lt122(arr, n-1);
    cout << "maxt stock income that can sell many times: " << v << endl;
    delete[] visited;
     */
    
    // weather can reach end point; LT 55;
    
    /*
    //int arr[] = { 2,3,1,1,4};
    int arr[] = {3,2,1,0,4};
    int n = sizeof(arr)/sizeof(arr[0]);
    bool s ; //= jump_55(arr, 0, n);
    // s = jump_55(arr, 0, n);
    int *visited = new int[n];
    fill(visited, visited + n, -1);
    //s = jump_55_v2(arr, 0, n, visited);
    
    //s = jump_55_v3(arr, n-1);
   
    s = jump_55_v4(arr, n-1);
    cout << "jumpy to the end : " << s << endl;
    */
    
    int s;
    int v[] = {60, 100, 120};
    int w[] = {10, 20, 30};
    int n = sizeof(v)/ sizeof(v[0]);
    int W = 50;
    //s = knapsack(v, w, W, n-1);
    
    vector< vector<int> > vec(n);
    for(int i = 0; i < n; i++){
        vec[i] = vector<int>(W+1);
        fill(vec[i].begin(), vec[i].end(), -1);
    }
    //s = knapsack_v2(v, w, W, n-1, vec);
    
    s = knapsack_v3(v, w, W, n-1);
    
    cout << "Knapsack problem result: " << s << endl;
}
