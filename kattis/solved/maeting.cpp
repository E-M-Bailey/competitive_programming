#include <bits/stdc++.h>

using namespace std;

bitset<100001> S{};

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	while (m--)
	{
		int x;
		cin >> x;
		S[x] = true;
	}
	for (int a : A)
		if (S[a])
			cout << a << ' ';
}
