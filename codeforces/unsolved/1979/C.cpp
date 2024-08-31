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
	int l = accumulate(begin(A), end(A), 1, lcm<int, int>);
	vector<int> X(n);
	for (int i = 0; i < n; i++)
		X[i] = l / A[i];
	if (accumulate(begin(X), end(X), 0ll) >= l)
		X = {-1};
	for (int x : X)
		cout << x << ' ';
	cout << '\n';
}
