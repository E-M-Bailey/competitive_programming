#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;
namespace vws = views;

using ll = long long;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		++n;
		vector<int> P(n);
		queue<int> L;
		P[1] = 0;
		vector<ll> T(n);
		for (int i = 1; i < n; ++i)
			for (int j = 0; j < 2; j++)
			{
				int c;
				cin >> c;
				if (c == 0)
				{
					if (j == 0)
						L.push(i);
					continue;
				}
				P[c] = i;
			}
		vector<int> S;
		S.reserve(n - 1);
		while (!L.empty())
		{
			int v = L.front();
			L.pop();
			if (v == 0)
				continue;
			if (T[P[v]] != 0)
				L.push(P[v]);
			S.push_back(v);
			T[P[v]] += 1 + ++T[v];
		}
		T[0] = 0;
		while (!S.empty())
		{
			int v = S.back();
			S.pop_back();
			T[v] += T[P[v]];
		}
		for (int i = 1; i < n; ++i)
			cout << T[i] << ' ';
		cout << '\n';
	}
}
