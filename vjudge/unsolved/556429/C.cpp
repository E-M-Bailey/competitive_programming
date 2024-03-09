#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	string s;
	int k;
	cin >> s >> k;
	int n = (int)s.size();
	vector<int> A(n);
	for (int i = 0; i < n; i++)
		A[i] = s[i] - '0';

	bool rep = false;
	vector<int> C(10);
	for (int i = 0; i < n; i++)
		rep |= C[A[i]]++;
	vector<priority_queue<int>> R(10);
	int mx = 9;

	for (int i = 0; i < n - 1; i++)
	{
		int &a = A[i];
		while (C[mx] == 0)
			mx--;
		if (a < mx)
		{
			if (k)
			{
				R[mx].push(a);
				a = mx;
				k--;
				C[mx]--;
			}
			else
			{
				int
			}
		}
		else if (mx == a)
		{
			C[a]--;
		}
		else
		{
			int b = a;
			while (C[b] == 0)
				b = R[b].top();
			if (k && b < mx)
			{
				
			}
		}
	}

	if (k % 2 && !rep)
		swap(A[n - 1], A[n - 2]);

	for (int a : A)
		cout << a;

	/*
	while (k--)
	{
		int l = -1, r = -1;
		int le = -1, re = -1;
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if ((l < 0 || l == i) && s[j] > s[i] && (r < 0 || s[j] >= s[r]))
				{
					l = i;
					r = j;
				}
				if (s[i] == s[j])
				{
					le = i;
					re = j;
				}
			}
		}
		if (l >= 0)
			swap(s[l], s[r]);
		else if (le >= 0)
			swap(s[le], s[re]);
		else
			swap(s[n - 2], s[n - 1]);
	}
	*/
}