#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, t;
	cin >> n >> t;
	int a, b, c;
	vector<int> T(n);
	cin >> a >> b >> c >> T[0];
	for (int i = 1; i < n; i++)
		T[i] = int(((long long)T[i - 1] * a + b) % c + 1);
	sort(begin(T), end(T));

	int cnt = 0, cur = 0;
	long long pen = 0;
	for (int tt : T)
	{
		cur += tt;
		if (cur > t)
			break;
		cnt++;
		pen += cur;
	}
	cout << cnt << ' ' << pen % 1000000007;
}