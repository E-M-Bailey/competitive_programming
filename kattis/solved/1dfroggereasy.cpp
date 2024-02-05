#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, s, m;
	cin >> n >> s >> m;
	s--;
	vector<int> A(n);
	for (int i = 0; i < n; i++)
		cin >> A[i];
	for (int h = 0;; h++)
	{
		if (s < 0)
		{
			cout << "left\n" << h;
			return 0;
		}
		if (s >= n)
		{
			cout << "right\n" << h;
			return 0;
		}
		int a = A[s];
		if (a == 0)
		{
			cout << "cycle\n" << h;
			return 0;
		}
		if (a == m)
		{
			cout << "magic\n" << h;
			return 0;
		}
		A[s] = 0;
		s += a;
	}
}
