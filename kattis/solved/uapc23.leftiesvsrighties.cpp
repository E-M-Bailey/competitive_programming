#include <bits/stdc++.h>
using namespace std;

int main()
{




	int T, n;
	cin >> T >> n;
	vector<int> L(T), R(T);
	for (int i = 0; i < n; i++)
	{
		int t;
		char c;
		cin >> t >> c;
		t--;
		(c == 'L' ? L : R)[t]++;
	}

	constexpr int NIL = numeric_limits<int>::max() / 2;

	int off = T * n;
	vector<int> C(2 * off + 1, NIL), P(2 * off + 1);
	C[off] = 0;
	vector<pair<int, int>> O;
	for (int i = 0; i < T; i++)
	{
		if (L[i] == 0 && R[i] == 0)
		{
			cout << -1;
			return 0;
		}
		O.clear();
		if (L[i] == 0)
			for (int r = 1; r <= R[i]; r++)
				O.emplace_back(r, r);
		else if (R[i] == 0)
			for (int l = 1; l <= L[i]; l++)
				O.emplace_back(-l, l);
		else
			for (int v = -L[i]; v <= R[i]; v++)
				O.emplace_back(v, v ? abs(v) : 2);

		P.swap(C);
		fill(begin(C), end(C), NIL);
		for (auto [v, c] : O)
		{
			for (int i = -off; i <= off; i++)
			{
				int j = i - v;
				if (j < -off || j > off)
					continue;
				C[i + off] = min(C[i + off], P[j + off] + c);
			}
		}
	}
	cout << (C[off] >= NIL ? -1 : C[off]) << endl;

	// 	for (int i = 0; i < n; i++)
	// 	{
	// 		int t;
	// 		char c;
	// 		cin >> t >> c;
	// 		t--;
	// 		(c == 'L' ? L : R)[t]++;
	// 	}
	// 	for (int t = 0; t < T; t++)
	// 	{
	// 		if (L[t] == 0 && R[t] == 0)
	// 		{
	// 			cout << -1;
	// 			return 0;
	// 		}
	// 	}
	// 	int ans = 0, c = 0, sl = 0, sr = 0;
	// 	unordered_set<int> I;
	// 	for (int i = 0; i < T; i++)
	// 		I.insert(i);
	// 	//sort(begin(I), end(I), [&](int t, int u) { int a = min(L[t], R[t]) >= 0, b = min(L[u], R[u]) >= 0; return a < b; });
	// 	for (int t = 0; t < T; t++)
	// 	{
	// 		if (L[t] == 0)
	// 		{
	// 			c++;
	// 			ans++;
	// 			sr += R[t] - 1;
	// 			I.erase(t);
	// 		}
	// 		else if (R[t] == 0)
	// 		{
	// 			c--;
	// 			ans++;
	// 			sr += L[t] - 1;
	// 			I.erase(t);
	// 		}
	// 	}
	// 	for (int t : I)
	// 	{
	// 		if (c > sl)
	// 		{
	// 			c--;
	// 			ans++;
	// 			sl += L[t] - 1;
	// 			sr += R[t];
	// 			I.erase(t);
	// 		}
	// 	}
}