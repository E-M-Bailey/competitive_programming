#include <bits/extc++.h>

using namespace std;
namespace rng = ranges;

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
		cout << (rng::is_sorted(A) ? n : 1) << '\n';
	}
}
