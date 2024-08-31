#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

typedef long long ll;

void go()
{
	int n, m;
	cin >> n >> m;
	int					   cp = 0;
	vector<pair<int, int>> A(n + m + 1);
	for (auto &[a, b] : A)
		cin >> a;
	for (auto &[a, b] : A)
	{
		cin >> b;
		cp += a > b;
	}
	if (cp <= n)
	{
		swap(n, m);
		for (auto &[a, b] : A)
			swap(a, b);
	}
	cp				 = 0;
	int			 del = -1;
	vector<bool> B(n + m + 1);
	ll			 sum = 0;
	for (int i = 0; i < n + m + 1; i++)
	{
		B[i] = A[i].first > A[i].second && cp < n;
		if (del < 0 && A[i].first > A[i].second && cp == n)
		{
			del = A[i].first - A[i].second;
		}
		sum += B[i] ? A[i].first : A[i].second;
		cp += B[i];
	}

	for (int i = 0; i < n + m + 1; i++)
	{
		if (B[i])
			cout << sum - A[i].first + del << ' ';
		else
			cout << sum - A[i].second << ' ';
	}
	cout << '\n';
}
