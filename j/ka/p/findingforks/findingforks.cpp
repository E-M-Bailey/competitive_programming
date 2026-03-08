#include "template.hpp"

using namespace std;
namespace rng = ranges;;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	vi32 A(n);
	for (int &a : A)
		cin >> a;
	auto it1 = rng::min_element(A);
	int m = *it1;
	A.erase(it1);
	cout << m + rng::min(A);
}
