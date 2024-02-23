#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	unordered_map<int, int> A;
	int l = 0, r = 0;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		A[a]++;
		r += a;
	}

	for (int t = 1;; t++)
	{
		auto it = A.find(t);
		int cur = it == end(A) ? 0 : it->second;
		r -= t * cur;
		if (l == r)
		{
			cout << t << '\n';
			return 0;
		}
		l += t * cur;
	}
}
