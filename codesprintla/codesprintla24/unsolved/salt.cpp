#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<long long> A(n);
	for (long long &a : A)
		cin >> a;

	if (n == 1)
	{
		cout << "0";
		return 0;
	}

	long long b = 62;
	while (b > 0)
	{
		if ((A.front() ^ A.back()) & (1ll << b))
			break;
		b--;
	}
	long long ans = 0;
	if (A.front() & (1 << b))
		ans |= 1ll << b;
	long long i = 0;
	while (!((A.front() ^ A[i]) & (1ll << b)))
		i++;
	while (--b >= 0)
		if (A[i] & (1ll << b))
			ans |= 1ll << b;
	
	cout << ans;
}