#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, q;
	cin >> n >> q;
	vector<bool> T(n, true);
	while (q--)
	{
		int i;
		cin >> i;
		i--;
		T[i] = !T[i];
	}
	cout << accumulate(begin(T), end(T), 0);
}
