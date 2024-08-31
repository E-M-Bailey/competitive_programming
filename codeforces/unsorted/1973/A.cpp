#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int A[3];
	for (int &a : A)
		cin >> a;
	sort(begin(A), end(A));
	if ((A[0] + A[1] + A[2]) % 2)
	{
		cout << "-1\n";
		return;
	}
	while (A[0] + A[1] < A[2])
	{
		A[2] -= 2;
	}
	cout << (A[0] + A[1] + A[2]) / 2 << '\n';
}
