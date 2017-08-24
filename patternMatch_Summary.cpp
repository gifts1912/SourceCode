#include <iostream>
#include <cstring>
#include <cmath>
#include <set>

using namespace std;
#define d 256

// C++ program for implementation of KMP pattern searching
// algorithm
#include<iostream>
#include <cstring>
#include <set>

using namespace std;

int * LPM(char *pat) {
	int m = strlen(pat);
	int *arr = new int[m];
	arr[0] = 0;
	int len = 0;
	int i = 1;
	while (i < m) {
		if (pat[i] == pat[len]) {
			len++;
			arr[i] = len;
			i++;	
		}
		else {
			if (len != 0) {
				len = arr[len - 1];
			}
			else {
				arr[i] = 0;
				i++;
			}
		}
	}
	for (int i = 0; i < m; i++) {
		cout << i << ":" << arr[i] << '\t';
	}
	cout << endl;
	return arr;
}

void KMPSearchV2(char *pat, char *txt) {
	int n = strlen(txt);
	int m = strlen(pat);
	int *lpm = new int[m];
	lpm = LPM(pat);
	
	int i = 0, j = 0;
	while (i < n) {
		while (j < m && txt[i] == pat[j]) {
			i++;
			j++;
		}
		if (j == m) {
			cout << "Match pos: " << i - m << endl;
			j = 0;
		}
		else {
			if (j == 0)
				i++;
			else
				j = lpm[j - 1];
		}
	}
}


/*
int main()
{
	char *txt = "ABABDABACDABABCABAB";
	char *pat = "ABAB";
	//LPM(pat);
	KMPSearchV2(pat, txt);
	return 0;
}

*/

void searchv2(char *pat, char *txt, int q) {
	int n = strlen(txt);
	int m = strlen(pat);
	int p = 0, t = 0;
	for (int i = 0; i < m; i++) {
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}
	int h = 1;
	for (int i = 0; i < m - 1; i++)
		h = (h*d) % q;

	//int h = (int)pow(d, m - 1) % q;

	for (int i = 0; i <= n - m; i++) {
		if (p == t) {
			int j;
			for (j = 0; j < m; j++) {
				if (txt[i + j] != pat[j]) {
					break;
				}
			}
			if (j == m) {
				cout << "Match at " << i << endl;
			}
		}
		if (i < n - m) {
			t = (d * (t - txt[i] * h) + txt[i + m]) % q;
		}
		if (t < 0) {
			t += q;
		}
	}

}
/*
int main()
{
	char txt[] = "GEEKS FOR GEEKS";
	char pat[] = "GEEK";
	int q = 101; // A prime number

	searchv2(pat, txt, q);
	return 0;
}
*/
int main()
{
	char *txt = "ABABDABACDABABCABAB";
	char *pat = "AAACAAAA";
	int * lmp = LPM(pat);
	for (int i = 0; i < strlen(pat); i++) {
		cout << i << ':' << lmp[i] << '\t';
	}
	cout << endl;
	//PSearch(pat, txt);
	getchar();
	return 0;
}
