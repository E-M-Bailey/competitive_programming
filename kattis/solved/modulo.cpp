#include <bits/stdc++.h>

using namespace std;

int main()
{
	bitset<42> S;
	int n;
	while (cin >> n)
		S[n % 42] = true;
	cout << S.count();
}
