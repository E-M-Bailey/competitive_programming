#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int m, n;
	int64_t A, B;
	cin >> m >> n >> A;

	int k = 0;
	vector<vector<int>> ID(m, vector<int>(m, -1));
	auto const id = [&ID, &k](int i, int j)
	{
		if (ID[i][j] < 0)
			ID[i][j] = k++;
		return ID[i][j];
	};

	vector<pair<int, int>> EA, EB;
	{
		vector<int> S;
		for (int i = 0; i < n; i++)
		{
			int l;
			cin >> l;
			S.resize(l);
			for (int &s : S)
			{
				cin >> s;
				s--;
			}
			for (int j = 0; j < l - 1; j++)
				EA.emplace_back(id(S[j], i), id(S[j + 1], i));
		}
	}

	//for (int i = 0; i < m; i++)
	//	for (int j = 0; j < n; j++)
	//		if (ID[i][j] >= 0)
	//			for (int kk = j + 1; kk < n; kk++)
	//				if (ID[i][kk] >= 0)
	//					EB.emplace_back(ID[i][j], ID[i][kk]);

	vector<vector<int>> GA(k);//, GB(k);
	for (auto [u, v] : EA)
	{
		GA[u].push_back(v);
		GA[v].push_back(u);
	}
	//for (auto [u, v] : EB)
	//{
	//	GB[u].push_back(v);
	//	GB[v].push_back(u);
	//}


	vector<vector<int>> DP(m, vector<int>(k, INT_MAX));
	priority_queue<pair<int, int>> PQ;
	for (int id : ID[0])
		if (id >= 0)
			PQ.emplace(0, id);
	for (int i = 0; i < k; i++)
		PQ.emplace(-(INT_MAX / 2), i);
	vector<int> CA(m, INT_MAX);
	for (int i = 0; i < m; i++)
	{
		while (!PQ.empty())
		{
			auto [d, v] = PQ.top();
			PQ.pop();
			d *= -1;
			if (d >= DP[i][v])
				continue;
			DP[i][v] = d;
			d++;
			for (int w : GA[v])
				if (d < DP[i][w])
					PQ.emplace(-d, w);
		}
		for (int id : ID[m - 1])
			if (id >= 0)
				CA[i] = min(CA[i], DP[i][id]);
		if (i < m - 1)
		{
			for (int j = 0; j < m; j++)
			{
				int d = INT_MAX / 2;
				for (int id : ID[j])
					if (id >= 0)
						d = min(d, DP[i][id]);
				for (int id : ID[j])
					if (id >= 0)
						PQ.emplace(-d, id);
			}
		}
	}

	int q;
	cin >> q;
	while (q--)
	{
		cin >> B;
		int64_t ans = INT64_MAX;
		for (int i = 0; i < m; i++)
			ans = min(ans, A * CA[i] + B * i);
		cout << ans << '\n';
	}

}