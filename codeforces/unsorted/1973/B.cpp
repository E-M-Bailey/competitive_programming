#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	vector<int> B;
	for (int j = 0; j < 30; j++)
		for (int i = 0; i < n; i++)
			if (A[i] & (1 << j))
			{
				B.push_back(j);
				break;
			}
	vector<int> I[30];
	for (int i = 0; i < n; i++)
		for (int j : B)
			if (A[i] & (1 << j))
				I[j].push_back(i);
	int ans = 1;
	for (int j : B)
	{
		ans = max(ans, I[j].front() + 1);
		ans = max(ans, n - I[j].back());
		for (int i = 1; i < (int)size(I[j]); i++)
			ans = max(ans, I[j][i] - I[j][i - 1]);
	}
	cout << ans << '\n';
}
