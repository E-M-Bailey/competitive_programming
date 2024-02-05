#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;

	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	vector<int> Sm{INT_MAX};
	for (int i = n; i-- > 0;)
		Sm.push_back(min(Sm.back(), A[i]));
	int M = 0;

	vector<int> ans;
	for (int i = 0; i < n; i++)
	{
		Sm.pop_back();
		if (M <= A[i] && A[i] < Sm.back())
			ans.push_back(A[i]);
		M = max(M, A[i]);
	}

	cout << ans.size();
	ans.resize(min((int)ans.size(), 100));
	for (int a : ans)
		cout << ' ' << a;
}
