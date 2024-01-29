#include <bits/stdc++.h>

using namespace std;

/*
template<size_t D>
vector<pair<array<int, D>, array<int, D>>> solve(array<int, D> dims, vector<array<int, D>> const &P)
{


	int n = (int)P.size();
	vector<int> Z(n);
	for (int i = 0; i < n; i++)
		Z[i] = P[i].back();
	sort(begin(Z), end(Z));
	Z.erase(unique(begin(Z), end(Z)), end(Z));
	int k = (int)Z.size();

	vector<vector<array<int, D - 1>>> Q(k);
	for (auto const &p : P)
	{
		int cc = lower_bound(begin(Z), end(Z), p.back()) - begin(Z);
		Q[cc].emplace_back(begin(p), prev(end(p)));
	}

	vector<vector<pair<array<int, D - 1>, array<int, D - 1>>>> qans(k);
	for (int i = 0; i < k; i++)
	{
		qans[i] = solve(array<int, D - 1>(begin(dims), prev(end(dims))));
		reverse(begin(qans[i]), end(qans[i]));
	}

	vector<pair<array<int, D>, array<int, D>>> pans(n);
	for (int i = 0; i < n; i++)
	{
		int cc = lower_bound(begin(Z), end(Z), p.back()) - begin(Z);
		copy(begin(qans[cc].back().first), end(qans[cc].back().first), begin(pans[i].first));
		copy(begin(qans[cc].back().second), end(qans[cc].back().second), begin(pans[i].second));
		qans[cc].pop_back();
		pans[i].first.back() =
	}


}
*/

int main()
{
	for (;;)
	{
		array<int, 3> dims;
		int n;
		for (int &d : dims)
			if (cin >> d, d < 0)
				return 0;
		cin >> n;

		bool good = true;

		vector<array<int, 3>> C(n), L(n), R(n);
		for (auto &CC : C)
			for (int &c : CC)
				cin >> c;
		for (int i = 0; i < n; i++)
		{
			for (int &l : L[i])
				cin >> l;
			for (int &r : R[i])
				cin >> r;
		}

		int64_t vol = 1;
		for (int i = 0; i < 3; i++)
			vol *= dims[i];

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 3; j++)
				good &= 1 <= L[i][j] && L[i][j] <= C[i][j] && C[i][j] <= R[i][j] && R[i][j] <= dims[j];
			for (int j = i + 1; j < n; j++)
			{
				bool isect = true;
				for (int k = 0; k < 3; k++)
					isect &= R[i][k] >= L[j][k] && R[j][k] >= L[i][k];
				good &= !isect;
			}
			int64_t cvol = 1;
			for (int k = 0; k < 3; k++)
				cvol *= R[i][k] - L[i][k] + 1;
			vol -= cvol;
		}
		good &= vol == 0;
		cout << (good ? "YES\n" : "NO\n");
	}
}