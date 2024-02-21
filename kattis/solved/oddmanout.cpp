#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int N;
	cin >> N;
	unordered_set<int> S;
	for (int i = 1; i <= N; i++)
	{
		cout << "Case #" << i << ": ";
		int G;
		cin >> G;
		while (G--)
		{
			int C;
			cin >> C;
			auto [it, ins] = S.insert(C);
			if (!ins)
				S.erase(it);
		}
		cout << *begin(S) << '\n';
		S.clear();
	}
}
