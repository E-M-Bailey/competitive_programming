#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	cin >> n;
	vector<int> X(n);
	for (int &a : X)
		cin >> a;

	map<pair<int, int>, int>	   A, B, C;
	map<tuple<int, int, int>, int> D;
	long long					   ans = 0;
	for (int i = 2; i < n; i++)
	{
		int a = X[i - 2], b = X[i - 1], c = X[i];
		ans += A[{a, b}] + B[{a, c}] + C[{b, c}] - 3 * D[{a, b, c}];
		A[{a, b}]++;
		B[{a, c}]++;
		C[{b, c}]++;
		D[{a, b, c}]++;
	}
	cout << ans << '\n';
}
