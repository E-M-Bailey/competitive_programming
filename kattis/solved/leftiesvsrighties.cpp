#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T, n;
	cin >> T >> n;
	vector<int> L(T), R(T);
	for (int i = 0; i < n; i++)
	{
		int	 t;
		char c;
		cin >> t >> c;
		t--;
		(c == 'L' ? L : R)[t]++;
	}

	constexpr int NIL = numeric_limits<int>::max() / 2;

	int			off = T * n;
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
	cout << (C[off] >= NIL ? -1 : C[off]) << '\n';
}
