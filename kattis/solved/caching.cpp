#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	int c, n, m;
	cin >> c >> n >> m;
	vector<int> A(m);
	vector<queue<int>> Q(n);
	for (int i = 0; i < m; i++)
	{
		cin >> A[i];
		Q[A[i]].push(i);
	}
	for (int i = 0; i < n; i++)
		Q[i].push(m);
	auto const cmp = [&](int i, int j)
		{
			return Q[i].front() < Q[j].front();
		};
	set<int, decltype(cmp)> C(cmp);
	int ans = 0;
	for (int a : A)
	{
		auto nd_a = C.extract(a);
		Q[a].pop();
		if (nd_a)
			C.insert(move(nd_a));
		else
		{
			ans++;
			if ((int)C.size() == c)
				C.extract(prev(C.end()));
			C.insert(a);
		}
	}
	cout << ans << '\n';
}
