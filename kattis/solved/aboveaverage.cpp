#include <bits/stdc++.h>

using namespace std;

int main()
{
	int C;
	cin >> C;
	while (C--)
	{
		int n;
		cin >> n;
		vector<int> A(n);
		int sum = 0;
		for (int &a : A)
		{
			cin >> a;
			sum += a;
		}
		int ct = 0;
		for (int a : A)
			ct += a * n > sum;
		cout << fixed << setprecision(3) << float(ct * 100) / float(n) << "%\n";
	}
}