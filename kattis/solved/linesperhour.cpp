#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	m *= 5;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	sort(begin(A), end(A));
	int s = 0, c = 0;
	for (int a : A)
		if (s + a <= m)
		{
			s += a;
			c++;
		}
	cout << c;
}