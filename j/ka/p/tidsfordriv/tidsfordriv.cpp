#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	ai32<13> C{};
	C.fill(4);
	int n;
	cin >> n;
	str s;
	while (n--)
	{
		cin >> s;
		s.pop_back();
		--C[s[0] == 'A' ? 0 : s[0] == 'J' ? 10 : s[0] == 'Q' ? 11 : s[0] == 'K' ? 12 : stoi(s) - 1];
	}
	cout << fixed << setprecision(5) << rng::max(C) / rng::fold_left(C, 0.0, plus{});
}
