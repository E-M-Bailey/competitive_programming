#include <bits/stdc++.h>

using namespace std;

int a, p;

int mult(int x, int y){
	return (int)((long long)x*y%(1<<p));
}

int exp(int a, int b){
	int res = 1;
	while(b){
		if(b%2 == 1) res = mult(res, a);
		a = mult(a, a);
		b /= 2;
	}
	return res;
}

void process(){
	cin >> a >> p;
	if(a%2 == 1){
		cout << 1 << endl;
		return;
	}
	else{
		int cnt = 0;
		for(int i = 1; i <= p; i++){
			//cout << i << endl;
			if(exp(a, i) == exp(i, a)){
				cnt++;
				//cout << i << endl;
			}
		}
		int k = ((p+a-1)/a);
		cnt += ((1<<p)/(1<<k)) - (p/(1<<k));
		cout << cnt << endl;
		return;
	}
	int cnt = 0;
	for(int i = 1; i <= (1<<p); i++){
		//cout << i << endl;
		if(exp(a, i) == exp(i, a)){
			cnt++;
			cout << i << endl;
		}
	}
	//cout << exp(a, 512) << " " << exp(512, a) << endl;
	cout << cnt << endl;
}

int main()
{
	int t;
	cin >> t;
	while(t--){
		process();
	}
}
