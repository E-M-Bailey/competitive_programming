#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<int> A(6);
	int x, y;
	for (int &a : A)
		cin >> a;
	cin >> x >> y;

	vector<int> B, C;
	for (int mask = 7; mask < 64; mask++)
	{
		if (__builtin_popcount(mask) != 3)
			continue;
		for (int i = 0; i < 6; i++)
			(mask & (1 << i) ? B : C).push_back(A[i]);
		sort(rbegin(B), rend(B));
		sort(rbegin(C), rend(C));
		if (accumulate(begin(B), end(B), 0) == x)
		{
			for (int b : B)
				cout << b << ' ';
			for (int c : C)
				cout << c << ' ';
			return 0;
		}
		B.clear();
		C.clear();
	}
}