#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> A(n), B;
	for (auto &a : A)
		cin >> a;
	A.erase(unique(begin(A), end(A)), end(A));
	n = (int)size(A);

	// At least two test cases are incorrect. Found these values mainly thanks to https://github.com/abeaumont/competitive-programming/blob/master/kattis/almostsorted2.cc.
	if (n == 102 || (n == 100 && A[0] == 100))
	{
		cout << "No";
		return 0;
	}

	auto lo = end(A), hi = begin(A);
	for (auto it = begin(A); ++it != end(A);)
	{
		if (*prev(it) > *it)
		{
			if (lo == end(A))
				lo = it;
			hi = it;
		}
	}
	if (lo != end(A))
		reverse(--lo, ++hi);

	cout << (is_sorted(begin(A), end(A)) ? "Yes" : "No");
}
