#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	ai32<6> C{};
	int n, m, x;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		++C[x - 1];
	}
	cout << (rng::max(C) + m >= n ? "Ja" : "Nej");
}
