#include <bits/stdc++.h>

using namespace std;

int					   n, m;
vector<pair<int, int>> A, B, C;
vector<bool>		   D;
vector<int>			   L, R;

auto const C1 = [](int a, int b)
{
	return B[a] < B[b];
};
auto const C2 = [](int a, int b)
{
	return C[a] < C[b];
};

bool works(int t)
{
	fill(begin(D), end(D), false);
	int a = 0, b = (int)A.size() - 1;

	// given m = min t+x, put a point at fixed t and t+x (x = m - t)
	int ct = 0;
	while (b >= 0)
	{
		while (D[L[a]])
			a++;
		ct++;
		int i = L[a];
		int x = B[i].first - t;
		while (b >= 0)
		{
			int j = R[b];
			if (C[j].first >= t - x)
			{
				b--;
				D[j] = true;
			}
			else
				break;
		}
	}

	return ct <= m;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	for (int k = 1; k <= t; k++)
	{
		cout << "Case " << k << ": ";
		cin >> n >> m;
		A.resize(n);
		B.resize(n);
		C.resize(n);
		D.resize(n);
		L.resize(n);
		R.resize(n);
		for (auto &[a, b] : A)
			cin >> a >> b;

		for (int i = 0; i < (int)size(A); i++)
		{
			B[i] = {A[i].first + A[i].second, i};
			C[i] = {A[i].first - A[i].second, i};
			L[i] = R[i] = (int)i;
		}

		sort(begin(L), end(L), C1);
		sort(begin(R), end(R), C2);

		int lo = -2000000, hi = min_element(begin(A), end(A))->first;

		while (lo < hi)
		{
			int mid = (lo + hi + 2000001) / 2 - 1000000;
			if (works(mid))
				lo = mid;
			else
				hi = mid - 1;
		}

		cout << lo << '\n';
	}
}
