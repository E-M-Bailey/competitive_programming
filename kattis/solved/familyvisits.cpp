#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, d;
	cin >> n >> d;
	
	vector<int> M(n), C(n);
	for (int i = 0; i < n; i++)
	{
		cin >> M[i] >> C[i];
	}

	vector<int> V(d);
	for (int &v : V)
		cin >> v;
	V.insert(begin(V), 0);

	vector<int> A;
	int ans = 0;
	
	for (int i = 0; i < d; i++)
	{
		int s = V[i], t = V[i + 1];
		A.assign(t - s + 1, 0);
		for (int j = s; j < t; j++)
		{
			for (int k = t - s + 1; k-- > 1;)
				A[k] = max(0, min(A[k] + M[j], A[k - 1] + M[j] - C[j]));
			A[0] += M[j];
		}
		
		if (A.back() > 0)
		{
			cout << "-1";
			return 0;
		}
		int cur = 0;
		while (A[cur] > 0)
			cur++;
		ans += cur;
	}
	cout << ans;
}