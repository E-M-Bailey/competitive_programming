#include "template.hpp"

using namespace std;
using namespace abbrev;

namespace
{

}

int main()
{
	ai32<24> C{};
	int n, k, m = 0;
	cin >> n >> k;
	while (n--)
	{
		int l, r;
		cin >> l >> r;
		for (int i = l; i < r; ++i)
			m += ++C[i] == k;
	}
	cout << m;
}
