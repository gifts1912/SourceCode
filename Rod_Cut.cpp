#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int Recursize_Rod_Cut(int *price, int n){
    if (n == 0){
        return 0;
    }
    int q = INT_MIN;
    for(int i = 1; i <= n; i ++){
        q = max(q,price[i] + Recursize_Rod_Cut(price, n-i));
    }
    return q;
}

int Bottom_Up_Rod_Cut(int *price, int n){
    int *r = new int[n+1];
    r[0] = 0;
    for(int i = 1; i <= n; i++){
        int q = INT_MIN;
        for(int j = 1; j <= i; j++){
            q = max(q, price[j] + r[i-j]); 
        }
        r[i] = q;
    }
    int res = r[n];
    delete [] r;
    return res;
}

int Memorized_Cut_Rod_Aux(int *p, int n, int *r){
    if(r[n] >= 0){
        return r[n];
    }
    int q = INT_MIN;
    if (n == 0){
        q = 0;
    }
    else {
        for(int i = 1; i <= n; i++){
            q = max(q, p[i] + Memorized_Cut_Rod_Aux(p, n - i, r));
        }
    }
    r[n] = q;
    return q;
}

int Memorized_Cut_Rod(int *p, int n){
    int *r = new int[n+1];
    fill_n(r, n+1, -1);
    
    int res = Memorized_Cut_Rod_Aux(p, n, r);
    delete[] r;
    return res;
}

int main(){
    int P[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n ; //= sizeof(P)/sizeof(P[0]);
    cin >> n;
    int *price = new int[n+1];
    price[0] = 0;
    memcpy(&(price[1]), P, sizeof(int) * (n+1));

    for(int i = 0; i <= n; i++){
        cout << price[i] << '\t';
    }
    cout << endl;

    int res, res2, res3;
    res = Recursize_Rod_Cut(price, n);

    res2 = Bottom_Up_Rod_Cut(price, n);

    res3 = Memorized_Cut_Rod(price, n);
    cout << "res: " << res << '\t' << "res2: " << res2 << '\t' << "res3: " << res3 << endl;

    return 0;
}
