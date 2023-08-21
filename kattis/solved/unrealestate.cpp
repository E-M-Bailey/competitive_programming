#include <bits/stdc++.h>

using namespace std;

int read()
{
	double x;
	cin >> x;
	return (int)round((x + 1000) * 100);
}

int main()
{
	int n;
	cin >> n;
	vector<int> X(2 * n), Y(2 * n);
	vector<tuple<int, int, int, int>> R(n);
	for (int i = 0; i < n; i++)
	{
		auto &[x1, y1, x2, y2] = R[i];
		X.push_back(x1 = read());
		Y.push_back(y1 = read());
		X.push_back(x2 = read());
		Y.push_back(y2 = read());
	}
	sort(begin(X), end(X));
	X.erase(unique(begin(X), end(X)), end(X));
	sort(begin(Y), end(Y));
	Y.erase(unique(begin(Y), end(Y)), end(Y));
	vector<int> IX(200001), IY(200001);
	int w = (int)X.size() - 1, h = (int)Y.size() - 1;
	vector<vector<int>> S(w + 1), E(w + 1);
	for (int i = 0; i <= w; i++)
		IX[X[i]] = i;
	for (int i = 0; i <= h; i++)
		IY[Y[i]] = i;
	for (int i = 0; i < n; i++)
	{
		S[IX[get<0>(R[i])]].push_back(i);
		E[IX[get<2>(R[i])]].push_back(i);
	}
	vector<int> cnt(h);
	int cur = 0;
	int64_t tot = 0;
	for (int i = 0; i < w; i++)
	{
		for (int j : S[i])
		{
			auto [x1, y1, x2, y2] = R[j];
			for (int y = IY[y1]; y < IY[y2]; y++)
				if (cnt[y]++ == 0)
					cur += Y[y + 1] - Y[y];
		}
		for (int j : E[i])
		{
			auto [x1, y1, x2, y2] = R[j];
			for (int y = IY[y1]; y < IY[y2]; y++)
				if (--cnt[y] == 0)
					cur -= Y[y + 1] - Y[y];
		}
		tot += (int64_t)cur * (X[i + 1] - X[i]);
	}
	cout << fixed << setprecision(2) << (double)tot / 10000;
}