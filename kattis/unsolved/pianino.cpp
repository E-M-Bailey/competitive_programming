#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	for (int i = n; i-- > 0;)
		A[i] -= A[0];

	vector<int> B(n);
	for (int i = 1; i < n; i++)
		B[i] = A[i] > A[i - 1] ? B[i - 1] + 1 : A[i] == A[i - 1] ? B[i - 1] : B[i - 1] - 1;

	int best = 0, bestk = 0, all = 0;

	unordered_map<int, int> F;
	for (int i = 0; i < n; i++)
	{
		if (B[i] == 0)
			all += A[i] == 0;
		else if ((A[i] == 0 || (A[i] > 0) == (B[i] > 0)) && A[i] % B[i] == 0)
		{
			int k = A[i] / B[i], f = ++F[k];
			if (f > best)
			{
				best = f;
				bestk = k;
			}
		}
	}

	cout << best + all << '\n' << bestk;


}