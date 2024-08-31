#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc;
	cin >> tc;
	while (tc--)
	{
		multimap<int, pair<bool, int>> S;
		vector<vector<int>>			   N;
		vector<int>					   T;

		int n;
		cin >> n;

		N.resize(n);
		for (int i = 0; i < n; i++)
		{
			int a;
			cin >> a;
			a		= -a;
			auto it = S.lower_bound(a);
			if (it != end(S))
			{
				N[it->second.second].push_back(i);
				if (it->second.first)
					S.erase(it);
				else
					it->second.first = true;
			}
			else
				T.push_back(i);
			S.emplace(a, pair{false, i});
		}

		cout << size(T) << '\n';
		for (int s : T)
		{
			queue<int> Q;
			Q.push(s);
			vector<int> C;
			while (!Q.empty())
			{
				int i = Q.front();
				Q.pop();
				C.push_back(i);
				for (int j : N[i])
					Q.push(j);
			}
			sort(begin(C), end(C));
			cout << size(C);
			for (int i : C)
				cout << ' ' << i + 1;
			cout << '\n';
		}
	}
}
