#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	vstr S(n);
	for (str &s : S)
	{
		cin >> s;
		rng::reverse(s);
	}
	rng::sort(S, greater<>{});
	for (str const &s : S)
		cout << s << ' ';
}
