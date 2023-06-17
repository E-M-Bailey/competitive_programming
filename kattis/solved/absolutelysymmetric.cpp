#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> A(n, vector<int>(n));
	for (auto &AA : A)
		for (int &a : AA)
			cin >> a;

	bool one = true, two = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a = A[i][j], b = A[j][i];
			one &= abs(a) == abs(b);
			two &= (a - b) % 2 == 0;
		}
	}

	if (one)
	{
		cout << "1\n";
		for (auto &AA : A)
		{
			for (int &a : AA)
				cout << a << ' ';
			cout << '\n';
		}
	}
	else if (two)
	{
		cout << "2\n";
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cout << (A[i][j] + A[j][i]) / 2 << ' ';
			cout << '\n';
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cout << (A[i][j] - A[j][i]) / 2 << ' ';
			cout << '\n';
		}
	}
	else
		cout << "-1";
}