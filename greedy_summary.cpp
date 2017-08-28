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
