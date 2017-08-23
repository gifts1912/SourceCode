#include <iostream>
#include <cstring>
#include <cmath>
#include <set>

using namespace std;
#define d 256

struct cstrless {
	bool operator() (const char *a, const char *b) {
		return strcmp(a, b) < 0;
	}
};

int * LPM(char *pat) {
	int m = strlen(pat);
	int *arr = new int[m];
	arr[0] = 0;
	arr[1] = 0;
	for (int i = 2; i <= m; i++) {
		char *pat_cur = new char[m];
		strncpy(pat_cur, pat, i);
		set<char *, cstrless> pre, pos;
		for (int j = 1; j < i; j++) {
			char *buf = new char[i];
			strncpy(buf, pat_cur, j);
			pre.insert(buf);

			strncpy(buf, pat_cur + i - j, j);
			pos.insert(buf);
		}

		int lpm = 0;
		for (char * ele : pre) {
			if (pos.find(ele) != pos.end()) {
				if (lpm < strlen(ele)) {
					lpm = strlen(ele);
				}
			}
		}
		arr[i] = lpm;
	}
	return arr;
}

void KMPSearch(char *pat, char *txt) {
	int m = strlen(pat);
	LPM(pat);
}

// Driver program to test above function


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
