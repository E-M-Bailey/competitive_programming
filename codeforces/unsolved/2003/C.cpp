#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		string s;
		cin >> n >> s;
		int F[128]{};
		for (char c : s)
			F[c]++;

		priority_queue<pair<int, char>> Q;
		pair<int, char> P{0, 0};
		string t;

		for (char c = 'a'; c <= 'z'; c++)
		{
			if (F[c])
				Q.emplace(F[c], c);
		}
		while (size(t) < size(s))
		{
			if (!Q.empty())
			{
				auto C = Q.top();
				Q.pop();
				if (P.first)
					Q.push(P);
				P = C;
			}
			t += P.second;
			P.first--;
		}
		cout << t << '\n';
	}
}

