#include <bits/stdc++.h>

using namespace std;

bool arith(vector<int> const &A)
{
	if ((int)A.size() < 2)
		return true;
	int d = A[1] - A[0];
	for (int i = 2; i < (int)A.size(); i++)
		if (A[i] - A[i - 1] != d)
			return false;
	return true;
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int m;
		cin >> m;
		vector<int> A(m);
		for (int &a : A)
			cin >> a;
		if (arith(A))
			cout << "arithmetic\n";
		else
		{
			sort(begin(A), end(A));
			if (arith(A))
				cout << "permuted arithmetic\n";
			else
				cout << "non-arithmetic\n";
		}
	}
}