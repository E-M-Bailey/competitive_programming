#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	vector<pair<int, int>> ans;

	for (;;)
	{
		int i = -1, j = -1;
		for (int k = 0; k < n; k++)
		{
			if (i == -1 || A[k] > A[i])
			{
				j = i;
				i = k;
			}
			else if (j == -1 || A[k] > A[j])
				j = k;
		}
		if (A[i] == 0)
			break;
		else if (A[j] == 0)
		{
			cout << "no";
			return 0;
		}
		ans.emplace_back(i, j);
		A[i]--;
		A[j]--;
	}
	cout << "yes";
	for (auto [i, j] : ans)
		cout << '\n' << i + 1 << ' ' << j + 1;
}