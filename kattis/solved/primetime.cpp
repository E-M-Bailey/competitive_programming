#include <bits/stdc++.h>

using namespace std;

int main()
{
	const int LIM = 10007;

	array<int, LIM + 1> LP{};
	for (int i = 2; i <= LIM; i++)
		if (LP[i] == 0)
			for (int j = i; j <= LIM; j += i)
				if (LP[j] == 0)
					LP[j] = i;

	array<array<int, 3>, LIM + 1> A{};
	const array<int, 3>			  UNIT = {INT_MAX, INT_MAX, INT_MAX};
	A[1]							   = UNIT;
	for (int p = 1, q = 2;;)
	{
		A[q]	= UNIT;
		A[q][0] = 1;
		for (int i = q - 1; i > p; i--)
		{
			int best = i + 1;
			for (int x = i, pr = LP[x]; pr; x /= pr, pr = LP[x])
			{
				int j = i / pr;
				if (min(A[j][2], j) <= min(A[best][2], best))
					best = j;
			}
			A[i]	= A[best];
			A[i][2] = min(A[i][2], best);
			rotate(begin(A[i]), begin(A[i]) + 2, end(A[i]));
		}
		if (q == LIM)
			break;
		p = q;
		do
			q++;
		while (LP[q] != q);
	}

	array<int, 3> ans{};

	int T;
	cin >> T;
	while (T--)
	{
		char c;
		int	 n;
		cin >> c >> n;
		array<int, 3> a = A[n];
		rotate(begin(a), begin(a) + (c == 'O' ? 0 : c == 'E' ? 2 : 1), end(a));
		for (int i = 0; i < 3; i++)
			ans[i] += a[i] == INT_MAX ? n : a[i];
	}

	for (int a : ans)
		cout << a << ' ';
}
