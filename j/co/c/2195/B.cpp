#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;
namespace vws = views;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		vector<int> A(n);
		for (int &a : A)
			cin >> a;
		vector<int> B;
		for (int i = 0; i < n; i += 2)
		{
			B.clear();
			for (int j = i; j < n; j = 2 * j + 1)
				B.push_back(A[j]);
			rng::sort(B);
			for (int j = i, k = 0; j < n; j = 2 * j + 1, ++k)
				A[j] = B[k];
		}
		cout << (rng::is_sorted(A) ? "YES\n" : "NO\n");
	}
}
