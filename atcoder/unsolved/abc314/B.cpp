#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> A(n);
	for (auto &AA : A)
	{
		int c;
		cin >> c;
		AA.resize(c);
		for (int &a : AA)
			cin >> a;
	}
	int x;
	cin >> x;

	vector<int> ans;
	int s = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		if (find(begin(A[i]), end(A[i]), x) == end(A[i]))
			continue;
		if ((int)A[i].size() < s)
		{
			ans.clear();
			s = (int)A[i].size();
		}
		if ((int)A[i].size() == s)
			ans.push_back(i);
	}
	cout << ans.size() << '\n';
	for (int a : ans)
		cout << a + 1 << ' ';
}