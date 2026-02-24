#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, r, c;
	cin >> n >> r >> c;
	vstr S(n);
	for (str &s : S)
		cin >> s;
	str s;
	for (int i = 0; i < r; ++i)
	{
		cin >> s;
		cout << (S[i * c] == s ? "left\n" : "right\n");
		for (int j = 1; j < c; ++j)
			cin >> s;
	}
}
