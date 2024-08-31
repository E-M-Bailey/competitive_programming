#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int m, x;
	cin >> m >> x;
	long long amt = 0;
	priority_queue<int> PQ;
	for (int i = 0; i < m; i++)
	{
		int c;
		cin >> c;
		amt -= c;
		PQ.push(c);
		while (amt < 0)
		{
			amt += PQ.top();
			PQ.pop();
		}
		amt += x;
	}
	cout << PQ.size() << '\n';
}
