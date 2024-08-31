#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

vector<int>	 P;
bitset<20000> C{};

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

int f(int n)
{
	return n + (n % 2 == 1 ? n * (n - 1) / 2 + 1 : n * (n - 2) / 2 + 2);
}

void go()
{
	if (P.empty())
	{
		P.push_back(1);
		for (int i = 2; i < 20000; i++)
			if (!C[i])
			{
				P.push_back(i);
				for (int j = i * 2; j < 20000; j += i)
					C[j] = true;
			}
	}

	int n;
	cin >> n;
	int k = 1;
	while (f(k) < n)
		k++;

	vector<int>	 ans;
	vector<bool> V(k, false);
	auto const	 add = [&](int a)
	{
		ans.push_back(a);
		if (!V[a])
		{
			ans.push_back(a);
			V[a] = true;
		}
	};

	vector<vector<bool>> S((k + 1) / 2);
	for (int s = 1; s * 2 < k; s++)
		S[s].resize(gcd(s, k));

	for (int v = 0; v < k; v++)
	{
		add(v);
		for (int s = 2; s * 2 < k; s++)
			if (!S[s][v % gcd(s, k)])
			{
				do
					add((ans.back() + s) % k);
				while (ans.back() != v);
				S[s][v % gcd(s, k)] = true;
			}
	}
	if (k > 2)
		add(0);
	if (k % 2 == 0 && k > 2)
		add(k / 2);

	for (int i = 0; i < n; i++)
		cout << P[ans[i]] << ' ';
	cout << '\n';
}
