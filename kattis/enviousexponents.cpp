#include <bits/stdc++.h>


using namespace std;

typedef long long ll;

ll N;
int k;

int cnt(ll N){
    int res = 0;
    while(N){
        if(N%2) res++;
        N /= 2;
    }
    return res;
}

int firstOne(ll N){
    int j = 0;
    while(N%2 == 0) {
            j++;
            N/=2;
    }
    return j;
}

int firstZero(ll N){
    int j = 0;
    while(N%2 == 1) {
        j++;
        N /= 2;
    }
    return j;
}

int main() {
    cin >> N >> k;

    N++;
    int b = cnt(N);
    while(k != b){
        if(k < b){
            N += ((ll)1 << firstOne(N));
            b = cnt(N);
        }
        else{
            N += ((ll)1 << firstZero(N));
            b = cnt(N);
        }
    }
    cout << N << endl;
}
