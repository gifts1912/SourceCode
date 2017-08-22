#include <iostream>
#include <cstring>
#include <cmath>


using namespace std;
#define d 256



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

int main()
{
	char txt[] = "GEEKS FOR GEEKS";
	char pat[] = "GEEK";
	int q = 101; // A prime number

	searchv2(pat, txt, q);
	return 0;
}
