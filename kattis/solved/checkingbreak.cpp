#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	for (;;)
	{
		array<int, 3> dims;
		int			  n;
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
