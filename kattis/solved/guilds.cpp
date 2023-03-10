#include <bits/stdc++.h>
using namespace std;
int dfs(const vector<int>& P, vector<int>& A, int v)
{
	if (A[v] >= 0)
		return A[v];
	else if (P[v] < 0)
		return A[v] = v;
	else
		return A[v] = dfs(P, A, P[v]);
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	unordered_map<string, int> N;
	vector<int> P;
	vector<int> L;
	while (n--)
	{
		string A, B;
		cin >> A >> B;
		int a = N.try_emplace(A, size(N)).first->second;
		int b = N.try_emplace(B, size(N)).first->second;
		P.resize(max(size(P), (size_t)max(a, b) + 1), -1);
		P[a] = b;
		L.push_back(a);
	}
	vector<string> D(size(N));
	for (const auto& [s, i] : N)
		D[i] = s;
	vector<int> A(size(N), -1);
	for (int i = 0; i < size(N); i++)
		dfs(P, A, i);
	for (int l : L)
		cout << D[l] << ' ' << D[A[l]] << endl;
}