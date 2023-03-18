#include <bits/stdc++.h>
using namespace std;

constexpr int MAXB = 317, MAXN = MAXB * MAXB;
int n, m, k, q, bl, bs = 0;
int A[MAXN]{};
int B[MAXN]{};
bool V[MAXN]{};
vector<int> BL[MAXB]{};
unordered_map<int, int> CC;

bool all_in(int i)
{
	for (int a : BL[i])
		if (!V[a])
			return false;
	return true;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
		(ignore = freopen(argv[1], "r", stdin)) = freopen(argv[2], "w", stdout);

	cin >> n;
	CC.reserve(n);
	for (int i = 0; i < n; i++)
	{
		int& a = A[i];
		cin >> a;
		a = CC.emplace(a, size(CC)).first->second;
	}
	k = size(CC);

	bl = 0;
	while (bl * bl < n)
		bl++;
	while (n < bl * bl)
		A[n++] = k;
	for (int i = 0; i < bl; i++)
	{
		BL[i].reserve(bl);
		for (int j = 0; j < bl; j++)
		{
			int a = A[i * bl + j];
			if (V[a])
				continue;
			V[a] = true;
			BL[i].push_back(a);
		}
		for (int a : BL[i])
			V[a] = false;
	}

	cin >> q;
	while (q--)
	{
		int i, m;
		cin >> i >> m;
		i--;
		bs = 0;
		while (m--)
		{
			int b;
			cin >> b;
			auto it = CC.find(b);
			if (it == CC.end())
				continue;
			b = it->second;
			if (V[b])
				continue;
			V[b] = true;
			B[bs++] = b;
		}
		int j = i;
		while (j % bl && V[A[j]])
			j++;
		if (V[A[j]])
		{
			while (j < n && size(BL[j / bl]) <= size(B) && all_in(j / bl))
				j += bl;
			while (j < n && V[A[j]])
				j++;
		}
		while (bs)
			V[B[--bs]] = false;
		cout << j - i << endl;
	}
}