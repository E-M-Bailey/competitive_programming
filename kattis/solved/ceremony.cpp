#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> H(n);
	for (int &h : H)
		cin >> h;
	sort(begin(H), end(H));
	int ans = n;
	for (int i = 0; i < n; i++)
		ans = min(ans, H[i] + (n - 1) - i);
	cout << ans;
}
