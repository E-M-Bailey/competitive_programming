#include <bits/stdc++.h>

using namespace std;

bitset<(1u << 31) + 1> BS;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;

	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= N >> i;
	N++;

	vector<vector<unsigned>> T(2 * N);
	for (int i = 0; i < n; i++)
	{
		unsigned a;
		cin >> a;
		T[i + N].push_back(a);
	}
	for (int i = n; i < N; i++)
	{
		T[i + N].push_back(1u << 31);
	}
	for (int i = N - 1; i > 0; i--)
	{
		auto &A = T[i * 2], &B = T[i * 2 + 1], &C = T[i];
		C.resize(A.size() + B.size());
		merge(begin(A), end(A), begin(B), end(B), begin(C));
		C.resize(unique(begin(C), end(C)) - begin(C));
	}

	int q;
	cin >> q;
	vector<unsigned> B;
	while (q--)
	{
		int i, m;
		cin >> i >> m;
		i--;
		B.resize(m);
		for (unsigned &b : B)
		{
			cin >> b;
			BS[b] = true;
		}

		const auto check = [&](int l)
		{
			if ((l & (l + 1)) == 0 || l >= 2 * N - 1)
				return false;
			if ((int)T[l].size() > m)
				return false;
			for (unsigned a : T[l])
				if (!BS[a])
					return false;
			return true;
		};

		int l = i + N;
		while (check(l))
			l = (l + 1) / 2;

		while (l < N)
		{
			if (check(l))
				l++;
			else
				l *= 2;
		}
		while (l < 2 * N && check(l))
			l++;

		cout << l - i - N << '\n';
		for (unsigned b : B)
			BS[b] = false;
		B.clear();
	}
}