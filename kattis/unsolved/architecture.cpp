#include <bits/stdc++.h>

using namespace std;

int main()
{
	int r, c;
	cin >> r >> c;
	vector<vector<int>> H(r, vector<int>(c, -1));
	vector<int> X(r), Y(c);
	for (int &x : X)
		cin >> x;
	for (int &y : Y)
		cin >> y;
	vector<int> Z(r + c);
	copy_n(begin(X), r, begin(Z));
	copy_n(begin(Y), c, begin(Z) + r);
	sort(begin(Z), end(Z));
	for (int i = 0; i < r + c; i++)
	{
		if (i && Z[i] == Z[i - 1])
			continue;

		for (int j = 0; j < r; j++)
			if (X[j] == Z[i])
				for (int k = 0; k < c; k++)
					if (H[j][k] == -1)
						H[j][k] = Z[i];
		for (int j = 0; j < c; j++)
			if (Y[j] == Z[i])
				for (int k = 0; k < r; k++)
					if (H[k][j] == -1)
						H[k][j] = Z[i];
	}

	bool good = true;
	for (int i = 0; i < r; i++)
	{
		int mx = -1;
		for (int j = 0; j < c; j++)
			mx = max(mx, H[i][j]);
		good &= mx == X[i];
	}
	for (int i = 0; i < c; i++)
	{
		int mx = -1;
		for (int j = 0; j < r; j++)
			mx = max(mx, H[j][i]);
		good &= mx == Y[i];
	}

	cout << (good ? "possible" : "impossible");
}