#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	vpi32 A;
	vi32 B;
	while (cin >> n, n)
	{
		A.resize(n);
		B.resize(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> A[i].first;
			A[i].second = i;
		}
		rng::sort(A, {}, &pi32::first);
		for (int &b : B)
			cin >> b;
		rng::sort(B);
		for (int i = 0; i < n; ++i)
			A[A[i].second].first = B[i];
		for (int i = 0; i < n; ++i)
			cout << A[i].first << '\n';
		cout << '\n';
	}
}
