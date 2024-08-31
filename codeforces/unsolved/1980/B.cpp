#include <bits/stdc++.h>

using namespace std;

#define sz(C) (int(size(C)))
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
	int n, f, k;
	cin >> n >> f >> k;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	f = A[f - 1];
	sort(rbegin(A), rend(A));
	bool a = A[k - 1] <= f, b = k < n && A[k] >= f;
	cout << (a ? b ? "MAYBE" : "YES" : "NO") << '\n';
}
