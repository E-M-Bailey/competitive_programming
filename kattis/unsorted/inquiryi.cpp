#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	int64_t sl = 0, sr = 0;
	for (int a : A)
		sr += a;
	int64_t ans = 0;
	for (int i = 0; i < n; i++)
	{
		sr -= A[i];
		sl += A[i] * A[i];
		ans = max(ans, sl * sr);
	}
	cout << ans;
}