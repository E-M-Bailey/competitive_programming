#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k, c;
	cin >> n >> k >> c;

	vector<priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>> A(n);
	auto const cmp = [&](int a, int b)
	{
		return A[a].top().first > A[b].top().first;
	};
	priority_queue<int, vector<int>, decltype(cmp)> B(cmp);

	for (int i = 0; i < n; i++)
	{
		int t, s;
		cin >> t >> s;
		s--;
		A[s].emplace(i, t);
		if (A[s].size() == 1)
			B.push(s);
	}

	vector<pair<int, int>> ans;
	vector<int> mult(n);
	while (!B.empty() && ans.size() < k)
	{
		int s = B.top();
		B.pop();
		ans.emplace_back(A[s].top());
		A[s].pop();
		if (++mult[s] < c && !A[s].empty())
			B.push(s);
	}

	for (int i = 0; i < n; i++)
		if (!A[i].empty())
			B.push(i);
	while (ans.size() < k)
	{
		int s = B.top();
		B.pop();
		ans.push_back(A[s].top());
		A[s].pop();
		if (!A[s].empty())
			B.push(s);
	}

	sort (begin(ans), end(ans));
	for (auto a : ans)
		cout << a.second << '\n';
}