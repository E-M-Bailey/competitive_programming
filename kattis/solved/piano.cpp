#include <bits/stdc++.h>

using namespace std;

template<bool W>
bool works(int n, array<vector<int>, 100> const &P)
{
	priority_queue<int, vector<int>, greater<int>> Q;
	for (int i = 0; i < 100; i++)
	{
		for (int e : P[i])
			Q.push(e);
		if (W || i % 7 < 5)
			for (int j = 0; !Q.empty() && j < n; j++)
				Q.pop();
		if (!Q.empty() && Q.top() <= i)
			return false;
	}
	return true;
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n, k;
		cin >> k >> n;
		n /= 2;
		array<vector<int>, 100> P;
		while (k--)
		{
			int s, e;
			cin >> s >> e;
			P[s - 1].push_back(e - 1);
		}
		if (works<0>(n, P))
			cout << "fine\n";
		else if (works<1>(n, P))
			cout << "weekend work\n";
		else
			cout << "serious trouble\n";
	}
}
