#include "template.hpp"

using namespace std;
namespace rng = ranges;
namespace vws = views;
using namespace abbrev;

int main()
{
	cout << "Gnomes:\n";
	i32 n;
	cin >> n;
	while (n--)
	{
		ai32<3> A;
		for (i32 &a : A)
			cin >> a;
		cout << (rng::is_sorted(A) || rng::is_sorted(A | vws::reverse) ? "Ordered\n" : "Unordered\n");
	}
}
