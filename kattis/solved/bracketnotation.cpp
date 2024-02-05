#include <bits/stdc++.h>

using namespace std;

void parse(char const *&ptr, vector<pair<int, int>> &S)
{
	int sz = (int)S.size(), l = sz + 4;
	S.emplace_back(l, l);
	S.emplace_back(-1, (int)',');
	S.emplace_back(0, 0);
	S.emplace_back(-1, (int)':');

	++ptr;
	while (*ptr == '(')
		parse(ptr, S);
	++ptr;

	int r	  = (int)S.size();
	S[sz + 2] = {r, r};
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	string B;
	cin >> B;

	vector<pair<int, int>> S;
	{
		char const *ptr = B.c_str();
		while (*ptr == '(')
			parse(ptr, S);
	}

	int			n = (int)S.size();
	vector<int> A(n + 1);

	for (bool done = false; !done;)
	{
		int len = 0;
		for (int i = 0; i < n; i++)
		{
			auto [a, b] = S[i];
			if (a < 0)
				len++;
			else if (b < 10)
				len++;
			else if (b < 100)
				len += 2;
			else if (b < 1000)
				len += 3;
			else if (b < 10000)
				len += 4;
			else
				len += 5;
			A[i + 1] = len;
		}

		done = true;
		for (int i = 0; i < n; i++)
		{
			auto &[a, b] = S[i];
			if (a >= 0)
			{
				done &= A[a] == b;
				b = A[a];
			}
		}
	}

	for (auto [a, b] : S)
	{
		if (a < 0)
			cout << (char)b;
		else
			cout << b;
	}
}
