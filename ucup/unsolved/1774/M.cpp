#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int N = 1 << n;
	vector<long long> A(N);
	for (auto &a : A)
		cin >> a;
	sort(rbegin(A), rend(A));
	long long ans = LLONG_MIN;
	for (int i = 0; i <= n; i++)
	{
		long long cur = accumulate(begin(A), begin(A) + (1 << i), 0ll);
		ans = max(ans, cur);
	}
	cout << ans;
}

