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
	if (A[0] == A[n - 1])
	{
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	string ans(n, 'R');
	ans[1] = 'B';
	cout << ans << '\n';
}
