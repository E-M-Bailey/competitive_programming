#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> v;

int gcd(int a, int b){
	if(a == 0 || b == 0) return a+b;
	return gcd(b%a, a);
}

void process(){
	cin >> N;
	v = vector<int>(N);
	int a=0, b=0, c=0;
	bool bo = true;
	for(int i = 0; i < N; i++){
		cin >> v[i];
		if(v[i] == 0){
			c++;
		}
		else if(v[i] == 1){
			a++;
		}
		else{
			b++;
		}
		if(b+c > a){
			if(c == 0){
				bo = false;
			}
			c--; a++;
		}
		//cout << i << endl;
	}
	if(bo){
		b += c;
		int n = 1+a;
		int d = n-b;
		int g = gcd(n, d);
		n /= g;
		d /= g;
		cout << n << " " << d << endl;
	}
	else{
		cout << -1 << endl;
	}
}

int main(){
	int t;
	cin >> t;
	for(int i = 0;  i < t; i++){
		process();
	}
}