#include <bits/stdc++.h>

using namespace std;

struct wall
{
	long double x;
	array<long double, 4> Y;
};

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	while (cin >> n, n >= 0)
	{

		vector<wall> W(n);
		for (wall& w : W)
		{
			cin >> w.x;
			for (long double& y : w.Y)
				cin >> y;
		}

		int N = n * 4 + 2;

		vector<vector<pair<int, long double>>> G(N);

		const auto conn = [&](long double x1, long double y1, long double x2, long double y2, int st, int ed, int i, int j)
		{
			for (int k = st; k < ed; k++)
			{
				long double f = (W[k].x - x1) / (x2 - x1);
				long double y = f * y2 + (1 - f) * y1;
				bool fnd = false;
				for (int l = 0; l < 4; l += 2)
				{
					long double L = W[k].Y[l], R = W[k].Y[l + 1];
					if (L <= y && y <= R)
					{
						fnd = true;
						break;
					}
				}
				if (!fnd)
					return;
			}
			long double dx = x2 - x1, dy = y2 - y1;
			G[i].emplace_back(j, sqrtl(dx * dx + dy * dy));
		};

		conn(0, 5, 10, 5, 0, n, 0, N - 1);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 4; j++)
			{
				int I = i * 4 + j + 1;
				long double x1 = W[i].x, y1 = W[i].Y[j];
				conn(0, 5, x1, y1, 0, i, 0, I);
				conn(x1, y1, 10, 5, i + 1, n, I, N - 1);
				for (int k = i + 1; k < n; k++)
					for (int l = 0; l < 4; l++)
					{
						int J = k * 4 + l + 1;
						long double x2 = W[k].x, y2 = W[k].Y[l];
						conn(x1, y1, x2, y2, i + 1, k, I, J);
					}
			}

		const long double INF = numeric_limits<long double>::infinity();
		vector<long double> D(N, INF);
		vector<bool> V(N);
		D[0] = 0;
		priority_queue<pair<long double, int>, vector<pair<long double, int>>, greater<pair<long double, int>>> Q;
		Q.emplace(0, 0);
		while (!Q.empty())
		{
			auto [d, v] = Q.top();
			Q.pop();
			if (V[v])
				continue;
			V[v] = true;
			for (auto [w, wt] : G[v])
				if (!V[w] && d + wt < D[w])
				{
					D[w] = d + wt;
					Q.emplace(d + wt, w);
				}
		}

		cout << fixed << setprecision(2) << D[N - 1] << '\n';
	}
}