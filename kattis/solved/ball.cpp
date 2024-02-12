#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	bitset<100000> S;
	vector<int>	   ans;
	for (int i = 0; i < n / 2 + 1; i++)
	{
		int a, b;
		cin >> a >> b;
		S[a - 1] = !S[a - 1];
		S[b - 1] = !S[b - 1];
	}
	for (int i = 0; i < n; i++)
		if (!S[i])
			cout << i + 1 << ' ';
}
