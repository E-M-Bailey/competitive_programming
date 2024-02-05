#include <bits/stdc++.h>

using namespace std;

vector<int> readDistr()
{
	vector<int> ans(201);
	int			a1, b1, a2, b2;
	cin >> a1 >> b1 >> a2 >> b2;
	for (int i = a1; i <= b1; i++)
		for (int j = a2; j <= b2; j++)
			ans[i + j]++;
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	vector<int> A	   = readDistr();
	vector<int> B	   = readDistr();
	int			gunnar = 0, emma = 0;
	for (int i = 0; i <= 200; i++)
		for (int j = 0; j <= 200; j++)
			if (i > j)
				gunnar += A[i] * B[j];
			else if (i < j)
				emma += A[i] * B[j];
	if (gunnar > emma)
		cout << "Gunnar" << '\n';
	else if (gunnar == emma)
		cout << "Tie" << '\n';
	else
		cout << "Emma" << '\n';
}
