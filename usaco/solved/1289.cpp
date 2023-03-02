#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, k;
	cin >> n >> k;
	k++;

	vector<int64_t> D(n);
	for (auto& d : D) cin >> d;

	int64_t cost = k;
	for (int i = 1; i < n; i++)
		cost = min(cost + k, cost + D[i] - D[i - 1]);
	cout << cost;
}