#include <iostream>
#include <cstring>
#include <cmath>


using namespace std;


const int d = 256;

void RabinKarp(char * txt, char *pat, int p){
    int n = strlen(txt);
    int m = strlen(pat);
    int p_hash = pat[0];
    int t_hash = txt[0];
    for(int i = 1; i < m; i++){
        p_hash = d * (p_hash + pat[i]) % p;
        t_hash  = d * (t_hash + txt[i]) % p;
    }
    int m_h = pow(d, m - 1);
    for(int i = 0; i < n-m; i++){
        if(p_hash == t_hash){
            for(int j = 0; j < m; j++){
                if(txt[i*m + j] != pat[j]){
                    break;
                }
            }
            cout << "Match at position: " << i << endl;
        }
        t_hash = (d * (t_hash - m_h * txt[i*m]) + txt[i * m + m])%p;
	if(t_hash < 0){
		t_hash += p;
	}
    }
    cout << endl;
}

int main(){

    char txt[] = "GEEKS FOR GEEKS";
    char pat[] = "GEEK";
    int q = 101;
    RabinKarp(txt, pat, q);
    return 0;
}
