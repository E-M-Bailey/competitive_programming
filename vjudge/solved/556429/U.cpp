#include <bits/stdc++.h>

using namespace std;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
	vector<vector<pair<int, int>>> G(N);
	for (int i = 0; i < M; i++)
	{
		G[R[i][0]].emplace_back(R[i][1], L[i]);
		G[R[i][1]].emplace_back(R[i][0], L[i]);
	}

	vector<int> D(N, -1);
	priority_queue<pair<int, int>> PQ;
	for (int i = 0; i < K; i++)
	{
		D[P[i]] = -2;
		PQ.emplace(0, P[i]);
	}
	while (!PQ.empty())
	{
		auto [d, v] = PQ.top();
		PQ.pop();
		if (D[v] >= 0)
			continue;
		if (D[v] == -1)
		{
			D[v] = -2;
			continue;
		}
		D[v] = -d;
		for (auto [w, l] : G[v])
			if (D[w] < 0)
				PQ.emplace(d - l, w);
	}

	return D[0];
}

/*
int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int N, M;
	cin >> N >> M;
	int R[M][2], L[M];
	for (int i = 0; i < M; i++)
		cin >> R[i][0] >> R[i][1];
	for (int i = 0; i < M; i++)
		cin >> L[i];
	int K;
	cin >> K;
	int P[K];
	for (int i = 0; i < K; i++)
		cin >> P[i];
	cout << travel_plan(N, M, R, L, K, P);
}*/