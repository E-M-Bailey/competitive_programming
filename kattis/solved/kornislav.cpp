#include <bits/stdc++.h>

using namespace std;

int main()
{
	int A[4];
	for (int &a : A)
		cin >> a;
	sort(begin(A), end(A));
	cout << A[0] * A[2];
}
