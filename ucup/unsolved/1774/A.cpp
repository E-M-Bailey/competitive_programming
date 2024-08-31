#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> C;

typedef long long ll;
ll constexpr M = 1000000007;

int n;
vector<int> T;
vector<bitset<75>> S;
vector<int> N20, N75;

array<ll, 76> P2;

pair<ll, ll> count(int i, vector<int> const &C)
{
	int num = 0;
	int num75 = 0;
	int j = i + 1;
	for (int c : C)
	{
		if (!S[i][c])
			return {0, 0};
		num += N20[i + c] - 1;
		for (; j < n && T[j] < T[i] + 75 && T[j] < T[i] + c + 20; j++)
			num75 += T[j] > T[i] + c;
	}
	return {P2[num], P2[num75]};
}

int main()
{
	P2[0] = 1;
	for (int i = 0; i < 75; i++)
		P2[i + 1] = P2[i] * 2 % M;

	C.push_back({0});
	for (int i = 20; i < 75; i++)
		C.push_back({0, i});
	for (int i = 20; i < 75; i++)
		for (int j = i + 20; j < 75; j++)
			C.push_back({0, i, j});

	cin >> n;
	T.resize(n);
	S.resize(n);
	N20.resize(n);
	N75.resize(n);

	for (int &t : T)
		cin >> t;

	for (int i = 0; i < n; i++)
		for (int j = i; j < n && T[j] < T[i] + 75; j++)
			S[T[j] - T[i]] = true;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 20; j++)
			N20[i] += S[i][j];
		N75[i] = S[i].count();
	}

	// cnt, total cost
	vector<pair<ll, ll>> DP(n + 1);
	DP.back() = {1, 0};
	for (int i = n; i-- > 0;)
	{
		DP[i] = DP[i + 1];
		ll tot = P2[N75[i]];
		for (auto const &CC : C)
		{
			auto [num, num75] = count(i, CC);
			
			int nxt = i + N75[i];
			while (nxt < n && T[nxt] < T[i] + CC.back() + 20)
				nxt++;

			tot = (M + tot - num75) % M;
		}
	}
}
