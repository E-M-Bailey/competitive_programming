#include <bits/stdc++.h>

using namespace std;

vector<int> necklaces(string const &s, int n, int i)
{
	vector<int> ans{i + 1};

	if (s[i] == '1')
	{
		for (int j = i + 1; j < n && s[j] == '1';)
			ans.push_back(++j);
		return ans;
	}

	vector<int> runs{-1};

	int l = 0, r = 0, j = i + 1;
	while (r < n && s[j] == '0')
	{
		ans.push_back(++j);
		runs.back()--;
	}
	if (j == n)
		return ans;

	ans.push_back(1);
	ans.push_back(++j);
	char c = '1';

	for (int j = i + 1; j < n; j++)
	{
		char d = s[j];
		if (d != c)
		{
			if (runs[l] == runs[r])
				l++;
			else
				l = 0;
			r++;
		}
		if (s[j] == '1')
			ans.push_back(++j);
	}
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		string s;
		cin >> s;
		int n = (int)size(s);

		vector<vector<int>> N(n);
		for (int i = 0; i < n; i++)
			N[i] = necklaces(s, n, i);
	}
}
