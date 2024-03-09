#include <bits/stdc++.h>

using namespace std;

int HP[10001];
int P[10001];
unordered_set<int> S;

int main()
{
	for (int i = 2; i <= 10000; i++)
	{
		if (HP[i])
			continue;
		for (int j = i; j <= 10000; j += i)
			HP[j] = i;
	}

	int n;
	cin >> n;

	while (n--)
	{
		int x;
		cin >> x;
		do
			P[x] += x;
		while (S.find(P[x]) != S.end());
		cout << P[x] << '\n';
		S.insert(P[x]);
	}
}