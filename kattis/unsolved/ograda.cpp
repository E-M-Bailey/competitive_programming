#include <bits/stdc++.h>
using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, x;
	cin >> n >> x;
	deque<pair<int, int>> w1{}, w2(x, 0);
	int64_t manual = 0, swoops = 0, curw = 0, curh = 0;

	for (int i = 0; i < x; i++)
	{
		int a;
		cin >> a;
		w1.push_back(min(w1.back(), a));
	}
	for (int i = 0; i < n; i++)
	{
		w2.push_back(max(w2.back(), w1.front()));
		int h = w2.front();
		if (h != curh)
		{
			swoops += (curw + x - 1) / x;
			curw = 0;
			curh = h;
		}
		curw++;
		int a = 0;
		if (i < n)
			cin >> a;
		manual += w1.push(a) - h;
	}
	swoops += (curw + x - 1) / x;
	cout << manual << '\n' << swoops;
}
