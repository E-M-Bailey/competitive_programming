#include <bits/stdc++.h>

using namespace std;

int n;
unordered_map<int64_t, int64_t> P;
vector<int64_t> A;

void solve(int l, int r, int k)
{
	if (k < 0 || l == r)
		return;	
	int m = r;
	int64_t bit = (int64_t)1 << k;
	while (A[m - 1] & bit)
		m--;
	solve(l, m, k - 1);
	solve(m, r, k - 1);

	for (int i = l; i < r; i++)
	{
		auto it1 = P.find(A[i]);
		auto it2 = P.find(it1->second ^ bit);
		if (it2 != P.end())
			it1->second ^= bit;
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	A.resize(n);
	P.reserve(n);
	for (auto &a : A)
	{
		cin >> a;
		P.emplace(a, a);
	}
	auto B = A;
	sort(begin(A), end(A));
	solve(0, n, 59);
	for (auto a : B)
		cout << P[a] << '\n';
}