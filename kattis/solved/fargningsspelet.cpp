#include <bits/extc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> A(n);

	int offset = 0, in;
	cin >> in;
	in--;
	if (m == 1)
	{
		offset = in;
		in = 0;
	}
	A[in] = 1;

	for (;;)
	{
		int out = -1;
		for (int i = 0; out < 0 && i < n; i++)
		{
			if (A[i] != 0 || (i > 0 && A[i - 1] == 0))
				continue;
			int a = i == 0 ? 0 : A[i - 1];
			int j = i;
			while (j < n - 1 && A[j + 1] == 0)
				j++;
			int b = j == n - 1 ? 0 : A[j + 1];

			if (a != 2 && b != 2)
				out = a == 1 ? j : i;
		}

		A[out] = 2;
		out += offset + 1;
		if (out > n)
			out -= n;
		cout << out << '\n' << flush;

		cin >> in;
		if (in < 0)
			break;
		in = in - 1 - offset;
		if (in < 0)
			in += n;
		A[in] = 1;
	}
}
