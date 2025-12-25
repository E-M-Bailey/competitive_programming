#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, d;
	cin >> n >> d;
	vector<int> P(n);
	for (int &p : P)
		cin >> p;
	sort(begin(P), end(P));
	
	int ans = 0;
	while (!P.empty())
	{
		ans++;
		int b = P.back() - d;
		while (!P.empty() && P.back() >= b)
			P.pop_back();
	}
	
	cout << ans;
}
