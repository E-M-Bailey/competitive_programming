#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<string> D(n);
	for (string &DD : D)
		cin >> DD;
	string X, d;
	cin >> X;
	reverse(begin(X), end(X));
	size_t ans = 0;
	while (!X.empty())
	{
		d += X.back();
		X.pop_back();
		auto it = find(begin(D), end(D), d);
		if (it != end(D))
			ans = ans * size(D) + (it - begin(D)), d.clear();
	}
	cout << ans;
}
