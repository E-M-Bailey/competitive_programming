#include <bits/extc++.h>

using namespace std;
namespace rng = ranges;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, x, y;
		cin >> n >> x >> y;
		vector<int> A(n);
		for (int &a : A)
			cin >> a;
		rotate(begin(A) + x, min_element(begin(A) + x, begin(A) + y), begin(A) + y);
		auto const pred = [a = A[x]](int b) { return b > a; };
		if (auto it = find_if(begin(A), begin(A) + x, pred); it != begin(A) + x)
			rotate(it, begin(A) + x, begin(A) + y);
		else
		{
			it = find_if(begin(A) + y, end(A), pred);
			rotate(begin(A) + x, begin(A) + y, it);
		}
		for (int n : A)
			cout << n << ' ';
		cout << '\n';
	}
}
