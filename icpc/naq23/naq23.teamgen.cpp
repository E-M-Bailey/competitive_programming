#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A, B;

int main()
{
	cin >> N;
	A = vector<int>(N+1);
	B = vector<int>(N+1);
	for(int i = 1; i <= N; i++){
		cin >> A[i] >> B[i];
	}
	int res = 0;
	for(int i = 1; i+2 <= N; i++){
		if(B[i] < i+2) continue;
		if(A[i+2] > i) continue;
		res++;
		i+=2;
	}
	cout << res << endl;
}