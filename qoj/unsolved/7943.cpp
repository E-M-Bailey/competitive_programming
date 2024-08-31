#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)
#define sz(C)		 int(C.size())

int N, M;
int C[200000];
vector<string> grid;
void process(){
	cin >> N >> M;
	for(int i = 0; i < M; i++){
		cin >> C[i];
	}
	vector<int> lis(1, -1);
	grid = vector<string>(N, string(M, '.'));
	int L = 0;
	for(int c = 0; c < M; c++){
		int mx = N-1;
		int ind = L;
		while(ind > 0 && lis[ind]+1 >= C[c]){
			mx = lis[ind];
			ind--;
		}
		if(mx > lis.back()){
			lis.push_back(max((int)lis.back()+1, mx-C[c]+1));
			L++;
		}
		for(int i = 0; i+1 < lis.size(); i++){
			lis[i] = min(lis[i], max(lis[i-1]+1, mx-C[c]+1));
		}
		for(int i = mx-C[c]+1; i <= mx; i++){
			grid[i][c] = '#';
		}
		for(int i : lis){
			cout << i << " ";
		}
		cout << endl;
	}
	cout << L << endl;
	for(int i = 0; i < N; i++){
		cout << grid[i] << endl;
	}
}


int main(int argc, char const *argv[])
{
	int t;
	cin >> t;
	for(int i = 0; i < t; i++) process();

}
