#pragma GCC optimize("no-stack-protector,unroll-loops")
#pragma GCC target("avx2,fma")

#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	// cin >> tc;
	while (tc--)
		go();
}

int x;

long long cnt(vector<int> const &A, vector<int> const &B)
{
	long long ans = 0;
	for (int b : B)
		ans += int(upper_bound(begin(A), end(A), x - b) - begin(A));
	return ans;
}

void go()
{
	int n, m;
	cin >> n >> m >> x;

	vector<int> A(n), B(m);
	for (int &a : A)
		cin >> a;
	for (int &b : B)
		cin >> b;
	
	vector<int> A2(n - 1), B2(m - 1);
	for (int i = 0; i < n - 1; i++)
		A2[i] = max(A[i], A[i + 1]);
	for (int i = 0; i < m - 1; i++)
		B2[i] = max(B[i], B[i + 1]);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cerr << (A[i] + B[j] <= x);
		cerr << endl;
	}
	cerr << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m - 1; j++)
			cerr << (A[i] + B2[j] <= x);
		cerr << endl;
	}
	cerr << endl;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m; j++)
			cerr << (A2[i] + B[j] <= x);
		cerr << endl;
	}
	cerr << endl;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m - 1; j++)
			cerr << (A2[i] + B2[j] <= x);
		cerr << endl;
	}
	cerr << endl;
	
	sort(begin(A), end(A));
	sort(begin(B), end(B));
	sort(begin(A2), end(A2));
	sort(begin(B2), end(B2));

	cout << cnt(A, B) - cnt(A, B2) - cnt(A2, B) + cnt(A2, B2);
}
