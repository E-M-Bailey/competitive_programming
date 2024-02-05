#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	unordered_set<int64_t> A, B, C;
	for (int i = 0; i < n; i++)
	{
		int64_t a;
		cin >> a;
		C.clear();
		B.insert(a);
		for (int64_t b : B)
		{
			int64_t g = gcd(a, b);
			C.insert(g);
			A.insert(g);
		}
		B.swap(C);
	}
	cout << (int)size(A);
}
