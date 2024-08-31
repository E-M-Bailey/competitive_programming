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
	int n, m, x;
	cin >> n >> m >> x;
	vector<bool> A(n), B(n);
	A[x - 1] = true;

	while (m--)
	{
		int cw;
		char c;
		cin >> cw >> c;
		int ccw = n - cw;
		for (int i = 0; i < n; i++)
			B[i] = (A[(i + ccw) % n] && c != '1') || (A[(i + cw) % n] && c != '0');
		A.swap(B);
	}

	cout << accumulate(ALL(A), 0) << '\n';
	for (int i = 0; i < n; i++)
		if (A[i])
			cout << i + 1 << ' ';
	cout << '\n';
}
