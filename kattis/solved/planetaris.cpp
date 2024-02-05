#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, a;
	cin >> n >> a;
	vector<int> E(n);
	for (int &e : E)
		cin >> e;
	sort(E.rbegin(), E.rend());
	int ans = 0;
	while (!E.empty() && E.back() < a)
	{
		a -= E.back() + 1;
		ans++;
		E.pop_back();
	}
	cout << ans;
}
