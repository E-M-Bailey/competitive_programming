#include <bits/stdc++.h>

using namespace std;

int prs(const string& str)
{
	int ans = 0;
	for (char c : str)
		if ('0' <= c && c <= '9')
			ans = ans * 10 + c - '0';
	return ans;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, m, s, v;
	cin >> n >> m >> s >> v;
	int64_t maxr2 = int64_t(100) * v * v * s * s;

	vector<pair<int, int>> pts(n + m);
	for (auto& [x, y] : pts)
	{
		string X, Y;
		cin >> X >> Y;
		x = prs(X);
		y = prs(Y);
	}

	vector<int> mat(m + n, -1);
	//vector<bool> V(n + m, false);
	queue<pair<int, int>> Q;
	vector<int> P(n + m, -1);


	for (int i = 0; i < n; i++)
	{
		fill(begin(P), end(P), false);

		Q.push(i);
		bool t = -1;
		while (!Q.empty())
		{
			auto [v] = Q.front();
			Q.pop();
			if (v >= n && mat[v] == -1)
			{
				t = v;
				break;
			}
			int st = v >= n ? 0 : n;
			int ed = v >= n ? n : n + m;
			for (int w = st; w < ed; w++)
			{
				auto [x1, y1] = pts[v];
				auto [x2, y2] = pts[w];
				int dx = x2 - x1, dy = y2 - y1;
				if (P[w] != -1)
					continue;
				if (dx * dx + dy * dy > maxr2)
					continue;
				if (v < n ^ mat[v] != w)
					continue;
				P[w] = v;
				
			}
		}
	}
}