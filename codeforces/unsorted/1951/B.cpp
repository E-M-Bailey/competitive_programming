
#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n, k;
	cin >> n >> k;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	k--;

	swap(A[k], A[0]);
	int ans = 0;
	while (ans < n - 1 && A[ans + 1] < A[0])
		ans++;
	swap(A[0], A[k]);

	int idx = 0;
	while (idx < n && A[idx] < A[k])
		idx++;
	if (idx < n && idx > 0)
	{
		swap(A[k], A[idx]);
		int ans2 = 1;
		while (ans2 + idx < n && A[ans2 + idx] < A[idx])
			ans2++;
		ans = max(ans, ans2);
	}

	cout << ans << '\n';
}
