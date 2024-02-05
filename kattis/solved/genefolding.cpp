#include <bits/stdc++.h>

using namespace std;

int64_t constexpr P1 = 1000000009, P2 = 1000000021, A1 = 5, A2 = 7, I1 = 200000002, I2 = 142857146;

bool op(vector<int> &A)
{
	int		n	= (int)A.size();
	int64_t h1l = 0, h1r = 0, h2l = 0, h2r = 0, b1 = 1, b2 = 1;
	for (int i = n - 1, j = n - 2; j >= 0; i--, j -= 2)
	{
		h1l = ((h1l + b1 * A[j + 1] - A[i] + P1) * I1 + b1 * A[j]) % P1;
		h2l = ((h2l + b2 * A[j + 1] - A[i] + P2) * I2 + b2 * A[j]) % P2;
		h1r = (h1r * A1 + A[i]) % P1;
		h2r = (h2r * A2 + A[i]) % P2;
		if (h1l == h1r && h2l == h2r)
		{
			A.erase(begin(A) + i, end(A));
			return true;
		}
		b1 = b1 * A1 % P1;
		b2 = b2 * A2 % P2;
	}
	return false;
}

int main()
{
	int C[128];
	C[(int)'A'] = 0;
	C[(int)'C'] = 1;
	C[(int)'G'] = 2;
	C[(int)'T'] = 3;

	string s;
	cin >> s;
	int			n = (int)s.size();
	vector<int> A(n);
	for (int i = 0; i < n; i++)
		A[i] = C[(int)s[i]];

	while (op(A))
	{}
	reverse(begin(A), end(A));
	while (op(A))
	{}
	cout << A.size();
}
