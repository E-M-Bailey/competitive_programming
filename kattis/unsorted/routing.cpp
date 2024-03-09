#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> ans;

void solve(const vector<int>& A, int N, int tidx, int bidx)
{
	//for (int a : A)
	//	cerr << a << ' ';
	//cerr << endl;
	if (N == 2)
	{
		ans[tidx].push_back(A[0] > A[1]);
		return;
	}

	int ps = ans[tidx].size();

	vector<array<vector<int>, 2>> S(N / 2);
	vector<pair<int, bool>> X(N / 2);
	for (int i = 0; i < N / 2; i++)
	{
		S[i][0].push_back(i);
		X[i].first = i;
	}

	for (int i = 0; i < N; i += 2)
	{
		int a = A[i], b = A[i + 1];
		bool d = (a ^ b ^ 1) & 1;
		a /= 2;
		b /= 2;
		auto [x, dx] = X[a];
		auto [y, dy] = X[b];
		d ^= dx ^ dy;
		//cerr << "merging " << a << ' ' << b << " (reps " << x << ' ' << y << ')' << (d ? " opposite" : " same") << endl;
		if (x != y)
		{
			int sx = int(S[x][0].size() + S[x][1].size());
			int sy = int(S[y][0].size() + S[y][1].size());
			if (sx < sy)
			{
				swap(a, b);
				swap(x, y);
				swap(dx, dy);
			}
			if (d)
				swap(S[y][0], S[y][1]);

			for (int c : S[y][0])
			{
				S[x][0].push_back(c);
				X[c] = make_pair(x, 0);
			}
			for (int c : S[y][1])
			{
				S[x][1].push_back(c);
				X[c] = make_pair(x, 1);
			}
			S[y][0].clear();
			S[y][1].clear();
		}
		//for (auto [x, dx] : X)
		//	cerr << ' ' << x << ' ' << dx << endl;
	}

	for (int x = 0; x < N / 2; x++)
	{
		if (S[x][0].empty() || (!S[x][1].empty() && *min_element(begin(S[x][0]), end(S[x][0])) > *min_element(begin(S[x][1]), end(S[x][1]))))
		{
			swap(S[x][0], S[x][1]);
			for (int c : S[x][0])
				X[c].second = 0;
			for (int c : S[x][1])
				X[c].second = 1;
		}
	}

	//cerr << "final:\n";
	//for (auto [x, dx] : X)
	//	cerr << ' ' << x << ' ' << dx << endl;

	for (int i = 0; i < N / 2; i++)
	{
		ans[tidx].push_back(X[i].second);
		ans[bidx].push_back(X[A[i * 2] / 2].second ^ (A[i * 2] & 1));
	}

	vector<int> B(N / 2), C(N / 2);
	for (int i = 0; i < N / 2; i++)
	{
		B[i] = A[i * 2 + ans[bidx][i + ps]] / 2;
		C[i] = A[i * 2 + !ans[bidx][i + ps]] / 2;
	}
	solve(B, N / 2, tidx + 1, bidx - 1);
	solve(C, N / 2, tidx + 1, bidx - 1);
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	while (cin >> n, n)
	{
		int N = 1 << n;
		vector<int> A(N);
		for (int& a : A)
			cin >> a;
		ans.resize(2 * n - 1);
		for (auto& row : ans)
			row.clear();
		solve(A, N, 0, 2 * n - 2);
		for (const auto& row : ans)
		{
			for (bool b : row)
				cout << b;
			cout << '\n';
		}
		cout << '\n';
		//cerr << endl;
	}
}