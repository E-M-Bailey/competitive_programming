#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m;
	cin >> n >> m;
	vstr D(n);
	getline(cin, D[0]);
	for (str &d : D)
		getline(cin, d);
	unordered_map<str, int> C;
	str s;
	while (m--)
	{
		cin >> s;
		cout << D[C[s]++] << '\n';
	}
}
