#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int grid[2001][2001];
int pre[2002][2002] = {{0}};
int N, M, K;

void reset(){
	int bc = max(1000-M-10, 0), ec = min(1000+M+10, 2001);
	int br = max(1000-N-10, 0), er = min(1000+N+10, 2001);
	for(int r = br; r <= er; r++){
		for(int c = bc; c <= ec; c++){
			grid[r][c] = 0;
		}
	}
}
void up(int r, int c){
	if(c < -1000 || c > 1000 || r < -1000 || r > 1000) return;
	grid[r+1000][c+1000]=1;
}
void pref(){
	int bc = max(1000-M-10, 0), ec = min(1000+M+10, 2001);
	int br = max(1000-N-10, 0), er = min(1000+N+10, 2001);
	for(int r = br; r <= er; r++){
		for(int c = bc; c <= ec; c++){
			pre[r][c] = pre[r][c-1] + pre[r-1][c] - pre[r-1][c-1] + grid[r-1][c-1];
		}
	}
}
int quer(int r1, int c1, int r2, int c2){
	//query [r1+1000, c1+1000]x[r2+1000, c2+1000]
	r1 += 1000; c1 += 1000; r2 += 1000; c2 += 1000;
	return pre[r2+1][c2+1] - pre[r1][c2+1] - pre[r2+1][c1] + pre[r1][c1];
}
string s, t;
void process(){
	reset();
	cin >> N >> M >> K;
	int U=0, L=0, R=0, D=0;
	int dr=0, dc=0;
	cin >> s;
	t = string(s.size(), '0');
	for(int i = 0; i < s.size(); i++){
		//cout << i << endl;
		if(s[i] == 'U') {
			t[i] = 'D';
			dr--;
		}
		if(s[i] == 'D') {
			t[i] = 'U';
			dr++;
		}
		if(s[i] == 'L') {
			t[i] = 'R';
			dc--;
		}
		if(s[i] == 'R') {
			t[i] = 'L';
			dc++;
		}
		U = max(U, -1*dr);
		D = max(D, dr);
		L = max(L, -1*dc);
		R = max(R, dc);
	}
	int r1 = U, c1 = L, r2 = N-1-D, c2 = M-1-R;
	if(r2 < r1 || c2 < c1){
		if(K == 0)cout << N*M << endl;
		else cout << 0 << endl;
		return;
	}
	int r = 0, c = 0;
	up(r, c);
	//cout << t << endl;
	for(int i = 0; i < s.size(); i++){
		if(t[i] == 'U'){
			r--;
		}
		else if(t[i] == 'D'){
			r++;
		}
		else if(t[i] == 'L'){
			c--;
		}
		else{
			c++;
		}
		up(r, c);
	}
	pref();
	
	for(int i = -4; i <= 4; i++){
		for(int e = -4; e <= 4; e++){
			//cout << grid[i+1000][e+1000];
		}
		//cout << endl;
	}

	int res = 0;
	K = (r2-r1+1)*(c2-c1+1) - K;
	for(int hr = 0; hr < N; hr++){
		for(int hc = 0; hc < M; hc++){
			int Q = quer(r1-hr, c1-hc, r2-hr, c2-hc);
			//cout << Q << endl;
			if(Q == K) res++;
		}
	}
	cout << res << endl;

}


int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		process();
	}
}