#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> original(2 * n), auxiliary;
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> original[2 * n - 1 - i];
	}

	int ans = 0;
	while (!original.empty())
	{
		if (!auxiliary.empty() && original.back() == auxiliary.back())
		{
			original.pop_back();
			auxiliary.pop_back();
		}
		else
		{
			auxiliary.push_back(original.back());
			original.pop_back();
		}
		ans++;
	}

	if (auxiliary.empty())
		cout << ans;
	else
		cout << "impossible";
}