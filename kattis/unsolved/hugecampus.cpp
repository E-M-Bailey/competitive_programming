#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	k++;
	vector<int> B;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		B.push_back(a);
		B.push_back(b);
		B.push_back(0);
	}

	vector<vector<int>> D(k, vector<int>(k, 100000)), D2;
	D[0][0] = 0;
	int pos = 0;
	char c;
	for (int nxt : B)
	{
		cin >> c;
		D2.assign(k, vector<int>(k, 100000));
		for (int x = 0; x < k; x++)
			for (int y = 0; y < k; y++)
			{
				int d = D[x][y];
				if (c == 'S')
					D2[x][y] = min(D2[x][y], d);
				if (x == pos)
					D2[nxt][y] = min(D2[nxt][y], d + 1);
				if (y == pos)
					D2[x][nxt] = min(D2[x][nxt], d + 1);
				if (x == pos && y == pos)
					D2[nxt][nxt] = min(D2[nxt][nxt], d + 1);
			}
		D.swap(D2);
		pos = nxt;
	}

	int ans = 100000;
	for (auto const &DD : D)
		for (int d : DD)
			ans = min(ans, d);
	cout << ans;
}