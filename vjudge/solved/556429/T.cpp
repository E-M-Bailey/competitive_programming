#include <bits/stdc++.h>

using namespace std;

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[])
{
	int lo = 0, hi = M;
	int Pans[M], Qans[M];
	int p[N], q[N];
	pair<int, int> I[N];
	vector<vector<int>> C;
	//auto const cmp = [&](int i, int j) { return C[i].size() > C[j].size(); };
	//priority_queue<int, vector<int>, decltype(cmp)> PQ(cmp);
	while (lo < hi)
	{
		int mid = (lo + hi) / 2;
		int pos = 0;
		for (int i = 0; i < N; i++)
		{
			p[i] = S[i];
			q[p[i]] = i;
		}

		//for (int i = 0; i < N; i++)
		//	cerr << p[i];
		//cerr << endl;
		for (int i = mid - 1; i >= 0; i--)
		{
			swap(p[q[X[i]]], p[q[Y[i]]]);
			swap(q[X[i]], q[Y[i]]);
			//cerr << i << ' ' << X[i] << ' ' << Y[i] << ' ';
			//for (int j = 0; j < N; j++)
			//	cerr << p[j];
			//cerr << endl;
		}

		C.clear();
		for (int i = 0; i < N; i++)
			I[i].first = -1;
		for (int i = 0; i < N; i++)
		{
			if (I[i].first >= 0)
				continue;
			int idx = (int)C.size();
			C.emplace_back();
			for (int j = i; I[j].first < 0; j = p[j])
			{
				I[j].first = idx;
				I[j].second = (int)C.back().size();
				C.back().push_back(j);
			}
		}
		//cerr << mid << endl;
		//for (auto const &CC : C)
		//{
		//	cerr << ' ';
		//	for (int c : CC)
		//		cerr << c;
		//}
		//cerr << endl;

		for (int i = 0; i < mid; i++)
		{

			swap(C[I[X[i]].first][I[X[i]].second], C[I[Y[i]].first][I[Y[i]].second]);
			swap(I[X[i]], I[Y[i]]);
			//cerr << " conj " << X[i] << ' ' << Y[i] << endl;
			//for (auto const &CC : C)
			//{
			//	cerr << ' ';
			//	for (int c : CC)
			//		cerr << c;
			//}
			//cerr << endl;

			if ((int)C.size() == N)
			{
				Pans[i] = Qans[i] = 0;
				continue;
			}

			while (C[pos].size() == 1)
				pos++;

			int u = C[pos][C[pos].size() - 2];
			int v = C[pos][C[pos].size() - 1];
			Pans[i] = u;
			Qans[i] = v;
			C[pos].pop_back();
			int idx = (int)C.size();
			C.emplace_back();
			C.back().push_back(v);
			I[v].first = idx;
			I[v].second = 0;
			//cerr << " swap " << u << ' ' << v << endl;
			//for (auto const &CC : C)
			//{
			//	cerr << ' ';
			//	for (int c : CC)
			//		cerr << c;
			//}
			//cerr << endl;
		}

		/*
		for (int i = 0; i < mid; i++)
		{
			if (PQ.size() < 2)
			{
				Pans[i] = Qans[i] = 0;
				continue;
			}

			swap(C[I[X[i]].first][I[X[i]].second], C[I[Y[i]].first][I[Y[i]].second]);
			swap(I[X[i]], I[Y[i]]);

			int a = PQ.top();
			PQ.pop();
			int b = PQ.top();
			PQ.pop();
			Pans[i] = C[a].back();
			Qans[i] = C[b].back();
			for (int j : C[a])
			{
				I[j].first = b;
				I[j].second = (int)C[b].size();
				C[b].push_back(j);
			}
			C[a].clear();
			PQ.push(b);
		}
		*/

		if ((int)C.size() < N)
			lo = mid + 1;
		else
		{
			hi = mid;
			for (int i = 0; i < mid; i++)
			{
				P[i] = Pans[i];
				Q[i] = Qans[i];
			}
		}
	}
	return lo;
}

/*
int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int N, M;
	cin >> N >> M;
	int S[N], X[M], Y[M];
	for (int i = 0; i < N; i++)
		cin >> S[i];
	for (int i = 0; i < M; i++)
		cin >> X[i] >> Y[i];
	int P[M], Q[M];
	int ans = findSwapPairs(N, S, M, X, Y, P, Q);
	cout << ans << '\n';
	for (int i = 0; i < ans; i++)
		cout << P[i] << ' ' << Q[i] << endl;
}*/