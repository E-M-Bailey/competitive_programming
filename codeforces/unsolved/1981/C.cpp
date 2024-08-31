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

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	if (*max_element(begin(A), end(A)) < 0)
		A[0] = 1;

	priority_queue<pair<int, int>> Q;
	for (int i = 0; i < n; i++)
		if (A[i] >= 0)
			Q.emplace(A[i], i);
	while (!Q.empty())
	{
		auto [a, i] = Q.top();
		Q.pop();
		if (i > 0 && A[i - 1] < 0)
			Q.emplace(A[i - 1] = a == 1 ? 2 : a / 2, i - 1);
		if (i < n - 1 && A[i + 1] < 0)
			Q.emplace(A[i + 1] = a == 1 ? 2 : a / 2, i + 1);
	}

	for (int i = 1; i < (int)size(A); i++)
		if (A[i] / 2 != A[i - 1] && A[i - 1] / 2 != A[i])
			A = {-1};
	for (int a : A)
		cout << a << ' ';
	cout << '\n';
}
