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

pair<int, vector<int>> solve(bool p, vector<int> const &A)
{
	int			n = (int)size(A);
	vector<int> BI, CI;
	for (int i = 1; i < n - 1; i += 2)
	{
		(p ? BI : CI).push_back(i);
		(p ? CI : BI).push_back(i + 1);
	}
	CI.push_back(p ? 0 : n - 1);
	auto const cmp = [&](int i, int j)
	{
		return A[i] < A[j];
	};
	sort(begin(BI), end(BI), cmp);
	sort(rbegin(CI), rend(CI), cmp);

	vector<int> B(n);
	int			lo = 0, hi = n;
	for (int i : BI)
		B[i] = hi--;
	for (int i : CI)
		B[i] = ++lo;
	B[p ? n - 1 : 0] = ++lo;
	int ans = 0;
	for (int i =  1; i < n - 1; i++)
		ans += A[i] + B[i] > max(A[i - 1] + B[i - 1], A[i + 1] + B[i + 1]);
	return {ans, B};
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	auto B = max(solve(0, A), solve(1, A)).second;
	for (int i = 0; i < n; i++)
		cout << B[i] << ' ';
	cout << '\n';
}
