#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	string dna;
	cin >> dna;

	int ca = 0, cb = 0;
	for (int i = 0; i < n; i++)
	{
		if (dna[i] == 'A')
			tie(ca, cb) = make_tuple(ca, min(ca, cb) + 1);
		else
			tie(ca, cb) = make_tuple(min(ca, cb) + 1, cb);
	}
	cout << ca;
}