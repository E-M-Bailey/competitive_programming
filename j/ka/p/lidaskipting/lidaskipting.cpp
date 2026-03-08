#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	str s;
	cin >> s;
	cout << (rng::fold_left(s, 0, plus{}) % 3 == 0 ? "Jebb" : "Neibb");
}
