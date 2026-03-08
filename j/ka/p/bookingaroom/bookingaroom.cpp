#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int r, n;
	cin >> r >> n;
	if (r == n)
	{
		cout << "too late";
		return 0;
	}
	au64<2> M{ -1ull, -1ull };
	while (n--)
	{
		int i;
		cin >> i;
		--i;
		M[i / 64] ^= 1ull << i;
	}
	cout << (M[0] ? countr_zero(M[0]) + 1 : countr_zero(M[1]) + 65);
}
