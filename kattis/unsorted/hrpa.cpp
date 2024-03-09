#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<long long> F{ 0, 1 };
	long long n;
	cin >> n;
	while (F.back() <= n)
		F.push_back(F.back() + F[F.size() - 2]);

	while (n)
	{
		while (F.back() > n)
			F.pop_back();
		n -= F.back();
	}
	cout << F.back();
}
