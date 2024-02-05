#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, dummy;
	cin >> n;
	vector<int>	 A{0}, X;
	vector<bool> S(n, true);
	A.reserve(n);
	X.reserve(n);
	for (int i = 1; i < n; i++)
	{
		for (int j = (i + 1) / 2; j-- > 0;)
			cin >> dummy;
		X.resize(i / 2);
		for (int &x : X)
		{
			cin >> x;
			S[x] = false;
		}
		bool fnd;
		if ((fnd = S[A[i - 1]]))
			A.push_back(i);
		for (int j = i; !fnd && j-- > 1;)
			if ((fnd = S[A[j - 1]] && S[A[j]]))
				A.insert(A.begin() + j, i);
		if (!fnd)
			A.insert(A.begin(), i);
		for (int x : X)
			S[x] = true;
	}
	for (int a : A)
		cout << a << ' ';
}
