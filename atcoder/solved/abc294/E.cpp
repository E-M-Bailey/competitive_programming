#include <bits/stdc++.h>
using namespace std;

int main()
{
	int64_t L;
	int n, m;
	cin >> L >> n >> m;
	deque<pair<int, int64_t>> A(n), B(m);
	for (auto& [v, l] : A)
		cin >> v >> l;
	for (auto& [v, l] : B)
		cin >> v >> l;
	int64_t i = 0, j = 0, ans = 0;
	while (i < L && j < L)
	{
		int64_t k = i + A.front().second, l = j + B.front().second;
		if (A.front().first == B.front().first)
			ans += max((int64_t)0, min(k, l) - max(i, j));
		if (k < l)
		{
			i = k;
			A.pop_front();
		}
		else
		{
			j = l;
			B.pop_front();
		}
	}
	cout << ans << endl;
}