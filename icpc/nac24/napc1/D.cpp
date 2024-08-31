#include <bits/stdc++.h>

using namespace std;

void process(){
	int N;
	cin >> N;
	vector<int> a(N);
	vector<int> b(N);
	for(int i = 0; i < N; i++) cin >> a[i];
	for(int i = 0; i < N; i++) cin >> b[i];
	int cnt = 0;
	int bad = 0;
	int xo = 0;
	int mx = 0;
	for(int i = 0; i < N; i++){
		if(b[i] == 2){
			if(a[i]%2 == 1){
				puts("Bob");
				return;
			}
			cnt++;
			bad = i;
		}
		if(b[i] == 1 && a[i] >= 2){
			cnt++;
			bad = i;
		}
		if(b[i] == 0){
			mx = max(mx, a[i]);
		}
		xo ^= a[i];
	}
	if(xo == 0 || cnt >= 2){
		puts("Bob");
		return;
	}
	if(cnt == 1){
		xo ^= a[bad];
		if(b[bad] == 1){
			xo ^= 1;
		}
		if(xo == 0){
			puts("Alice");
			return;
		}
		else{
			puts("Bob");
			return;
		}
	}
	bool poss = false;
	for(int i = 0; i < N; i++){
		int need = xo^a[i];
		if(need%2 == 0 && b[i] == 1) continue;
		if(need%2 == 1 && b[i] == 2) continue;
		if(need < a[i]){
			poss = true;
		}
	}
	if(poss){
		puts("Alice");
	}
	else{
		puts("Bob");
	}
}

int main()
{
	int t;
	cin >> t;
	while(t--){
		process();
	}
}
