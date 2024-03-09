#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> P;

vector<vector<vector<vector<float>>>> DP;

float f(int a, int b, int c, int d, int acc)
{
	if (min({ a, b, c, d }) < 0)
		return 0;
	auto &dp = DP[a][b][c][d];
	if (dp < 0)
	{
		auto p = P[b + 2 * c + 3 * d];
		dp = max((float)acc, (a * f(a - 1, b + 1, c, d, acc + p) + b * f(a, b - 1, c + 1, d, acc + p) + c * f(a, b, c - 1, d + 1, acc + p)) / n);
	}
	return dp;
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin >> n;
	P.resize(3 * n);
	for (int &p : P)
		cin >> p;
	DP.resize(n + 1, vector<vector<vector<float>>>(n + 1, vector<vector<float>>(n + 1, vector<float>(n + 1, -1))));
	cout << fixed << setprecision(6) << f(n, 0, 0, 0, 0);
}