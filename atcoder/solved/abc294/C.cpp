#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> A(n), B(m);
	for (int& a : A)
		cin >> a;
	for (int& b : B)
		cin >> b;
	vector<pair<int, int>> C;
	for (int i = 0; i < n; i++)
		C.emplace_back(A[i], i);
	for (int j = 0; j < m; j++)
		C.emplace_back(B[j], ~j);
	sort(begin(C), end(C));
	for (int i = 0; i < n + m; i++)
	{
		int j = C[i].second;
		if (j >= 0)
			A[j] = i;
		else
			B[~j] = i;
	}
	for (int a : A)
		cout << a + 1 << ' ';
	cout << endl;
	for (int b : B)
		cout << b + 1 << ' ';
}