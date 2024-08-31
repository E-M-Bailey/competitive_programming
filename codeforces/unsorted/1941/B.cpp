#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
		go();
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	bool good = true;
	for (int i = 0; good && i + 2 < n; i++)
	{
		good &= A[i] >= 0;
		A[i + 1] -= A[i] * 2;
		A[i + 2] -= A[i];
	}

	cout << (good && A[n - 2] == 0 && A[n - 1] == 0 ? "YES\n" : "NO\n");
}
