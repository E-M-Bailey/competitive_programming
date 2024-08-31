#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)
#define sz(C)		 int(C.size())

struct RMQ
{
	vector<int> A;
	vector<vector<int>> jmp;
	RMQ(){

	}
	RMQ(const vector<int> &V) : jmp(1, V), A(V)
	{
		for(int i = 0; i < A.size(); i++){
			jmp[0][i] = i;
		}
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k)
		{
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j, 0, sz(jmp[k])) {
				int l = jmp[k-1][j];
				int r = jmp[k-1][j+pw];
				if(A[l] > A[r]){
					jmp[k][j] = l;
				}
				else{
					jmp[k][j] = r;
				}
			}
		}
	}
	int query(int a, int b)
	{
		if (a >= b)
			return 0;
		int dep = 31 - __builtin_clz(b - a);
		//cout << dep << " " << a << " " << b << " " << jmp.size() << endl;
		int l = jmp[dep][a];
		int r = jmp[dep][b - (1 << dep)];
		if(A[l] > A[r]){
			return l;
		}
		return r;
	}
};

RMQ Q;
vector<int> A;
vector<int> res;

void solve(int l, int r){
	if(r < l) return;
	int N = r-l+1;
	int ind = Q.query(l, r+1);
	//cout << ind << endl;
	assert(l <= ind && r >= ind);
	res[ind] = N;
	solve(l, ind-1);
	solve(ind+1, r);
}


int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int N;
	cin >> N;
	A = vector<int>(N, 0);
	res = vector<int>(N, 0);
	for(int i = 0; i < N; i++){
		cin >> A[i];
	}
	Q = RMQ(A);
	//cout << "done\n";

	solve(0, N-1);
	for(int i = 0; i < N; i++){
		cout << res[i] << " ";
	}
	cout << endl;

}
