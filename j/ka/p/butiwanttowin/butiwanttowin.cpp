#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	vi32 C(n);
	for (i32 &c : C)
		cin >> c;
	rng::sort(C);
	i64 m = rng::fold_left(C, i64{}, plus{}) - 2 * C[n - 2];
	i32 k = 0;
	while (k + 2 < n && m >= 0)
		m -= 2 * C[k++];
	if (m >= 0)
		cout << "IMPOSSIBLE TO WIN";
	else
		cout << k;
}
