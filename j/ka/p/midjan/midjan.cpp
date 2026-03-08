#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m;
	cin >> n >> m;
	vi32 M(n), T(m);
	usi32 MM, TT;
	for (int &m : M)
	{
		cin >> m;
		MM.insert(m);
	}
	for (int &t : T)
	{
		cin >> t;
		TT.insert(t);
	}
	for (int m : M)
		if (!TT.contains(m))
			cout << m << ' ';
	cout << '\n';
	for (int t : T)
		if (!MM.contains(t))
			cout << t << ' ';
}
