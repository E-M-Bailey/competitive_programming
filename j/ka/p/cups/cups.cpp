#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	astr<2000> C;
	while (n--)
	{
		str a, b;
		cin >> a >> b;
		if (a[0] <= '9')
			C[stoi(a)] = std::move(b);
		else
			C[2 * stoi(b)] = std::move(a);
	}
	for (auto const &c : C)
		if (!c.empty())
			cout << c << '\n';
}
