#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	vector<int> D(4096, -1);
	D[0] = 0;
	queue<int> Q;
	Q.push(0);
	vector<int> nxt;
	while (!Q.empty())
	{
		int x = Q.front(), d = D[x];
		Q.pop();
		for (int v = 1; v < 16; v++)
			nxt.push_back(x | v);
		for (int amt = 1; amt < 8; amt++)
		{
			nxt.push_back(x << amt);
			nxt.push_back(x + (x << amt)); // amt = 0 case covered by LSL with amt = 1
			nxt.push_back((x >> amt) | (x << (12 - amt)));
		}
		nxt.push_back(x + 1);
		nxt.push_back(~x);
		for (int a : nxt)
		{
			a &= 0xfff;
			if (D[a] < 0)
			{
				D[a] = d + 1;
				Q.push(a);
			}
		}
		nxt.clear();
	}

	int t;
	cin >> t;
	while (t--)
	{
		int x;
		cin >> x;
		cout << D[x] << '\n';
	}
}