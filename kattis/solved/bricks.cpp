#include <bits/stdc++.h>

using namespace std;

int main()
{
	map<array<int, 6>, int> S, T;
	S[array<int, 6>{}] = 0;
	
	int ans = 0;

	int n;
	cin >> n;
	array<int, 6>  A, B, C, D;
	vector<string> G;
	while (n--)
	{
		T.clear();
		fill(begin(A), end(A), 0);
		fill(begin(B), end(B), 0);
		fill(begin(C), end(C), 0);
		fill(begin(D), end(D), 0);

		int w, h, s;
		cin >> w >> h >> s;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
				char c;
				cin >> c;
				if (c == '#')
				{
					A[i]++;
					B[h - 1 - i]++;
					C[j]++;
					D[w - 1 - j]++;
				}
			}

		for (array<int, 6> X : {A, B, C, D})
		{
			for (int i = 0; i == 0 || X[6 - i] == 0; i++)
			{
				for (auto ent : S)
				{
					auto Y = ent.first;
					int	 t = ent.second;
					for (int j = i; j < 6; j++)
					{
						if ((Y[j] += X[j - i]) >= 3)
						{
							t += s * Y[j];
							Y[j] = 0;
						}
					}
					T[Y] = max(T[Y], t);
					ans = max(ans, t);
				}
			}
		}

		T.swap(S);
	}
	
	cout << ans;
}
