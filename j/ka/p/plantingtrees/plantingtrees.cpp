#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, x, m = 0;
	cin >> n;
	vi32 T(n);
	for (int &t : T)
		cin >> t;
	rng::sort(T, greater{});
	for (int i = 0; i < n; ++i)
		m = max(m, T[i] + i + 2);
	cout << m;
}
