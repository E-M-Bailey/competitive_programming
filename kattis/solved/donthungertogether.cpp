#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;
	vector<pair<int, int>> A(n);
	for (auto &[q, f] : A)
		cin >> q >> f;

	priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> Q;
	double																					 lo = 0, hi = 1e9;
	for (int x = 0; x < 80; x++)
	{
		double mid	= (lo + hi) / 2;
		bool   good = true;
		for (int i = 0; i < n; i++)
		{
			auto [q, f] = A[i];
			Q.emplace(f, q);
			double rem = k * mid;
			while (!Q.empty() && Q.top().first <= i)
				Q.pop();
			while (rem > 0 && !Q.empty())
			{
				double amt = min(rem, Q.top().second);
				rem -= amt;
				if ((const_cast<double &>(Q.top().second) -= amt) == 0)
					Q.pop();
			}
			if (rem > 0)
			{
				good = false;
				break;
			}
		}
		(good ? lo : hi) = mid;
		while (!Q.empty())
			Q.pop();
	}
	if (lo == 0)
		cout << -1;
	else
		cout << fixed << setprecision(10) << ((lo + hi) / 2);
}
