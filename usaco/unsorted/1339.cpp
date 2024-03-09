#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	vector<int> A(k), B(k);
	for (int &a : A)
	{
		cin >> a;
		a--;
	}
	for (int &b : B)
	{
		cin >> b;
		b--;
	}

	vector<bool> isol(n, true);
	for (int a : A)
		isol[a] = false;
	for (int b : B)
		isol[b] = false;

	unordered_map<int, int> IA;
	for (int i = 0; i < k; i++)
		IA[A[i]] = i;

	auto const cmp_cyc = [&]()
		{
			vector<int> F(k);
			for (int i = 0; i < k; i++)
			{
				auto it = IA.find(B[i]);
				if (it == IA.end())
					continue;
				int diff = (i + k - it->second) % k;
				F[diff]++;
			}
			return *max_element(begin(F), end(F));
		};

	int ans = cmp_cyc();
	reverse(begin(B), end(B));
	ans = max(ans, cmp_cyc()) + accumulate(begin(isol), end(isol), 0);

	cout << ans;
}