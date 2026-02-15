#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;
namespace vws = views;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		array<int, 6> C{};
		while (n--)
		{
			int a;
			cin >> a;
			--a;
			array<int, 6> D{};
			D.fill(INT_MAX);
			for (int i = 0; i < 6; ++i)
				for (int j = 0; j < 6; ++j)
					if (j != i && j + i != 5)
						D[j] = min(D[j], C[i] + (a != j));
			C = D;
		}
		cout << rng::min(C) << '\n';
	}
}
