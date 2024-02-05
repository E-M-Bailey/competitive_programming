#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int64_t> W(n + 1);
	W[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		W[i] = W[i - 1];
		if (i > 1)
			W[i] += W[i - 2];
		if (i > 2)
			W[i] += W[i - 3];
	}
	cout << W.back();
}
