#include <bits/stdc++.h>

using namespace std;

typedef tuple<int64_t, int> T;

int main()
{
	int n;
	cin >> n;
	priority_queue<T, vector<T>, greater<T>> PQ;
	for (int i = 0; i < n; i++)
	{
		int64_t a;
		cin >> a;
		PQ.emplace(a, INT_MAX);
	}
	int ans = 0;
	while (!PQ.empty())
	{
		auto [a, b] = PQ.top();
		PQ.pop();
		if (b == INT_MAX)
		{
			PQ.emplace(a + 200000, ans + 2);
			PQ.emplace(a + 300000, ans + 3);
			PQ.emplace(a + 400000, ans + 4);
		}
		else
			ans = max(ans, b);
	}
	cout << ans;
}