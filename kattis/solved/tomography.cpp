#include <bits/stdc++.h>

using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;
	vector<int> A(m), B(n);
	int sum = 0;
	for (int &a : A)
	{
		cin >> a;
		sum += a;
	}
	for (int &b : B)
	{
		cin >> b;
		sum -= b;
	}

	vector<vector<int>> Q(n);
	int cnt = 0;
	for (int i = 0; i < m; i++)
		if (--A[i] >= 0)
		{
			Q[A[i]].push_back(i);
			cnt++;
		}


	vector<int> C(m);
	for (int b : B)
	{
		if (cnt < b)
		{
			cout << "No";
			return 0;
		}
		int pos = n - 1;
		for (int i = b; i-- > 0;)
		{
			while (Q[pos].empty())
				pos--;
			C[i] = Q[pos].back();
			Q[pos].pop_back();
		}
		for (int i = b; i-- > 0;)
		{
			int c = C[i];
			if (--A[c] >= 0)
				Q[A[c]].push_back(c);
			else
				--cnt;
		}
	}

	cout << (cnt == 0 ? "Yes" : "No");

}