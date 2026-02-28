#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vi32 T(n), L(m);
	for (int &t : T)
		cin >> t;
	for (int &l : L)
		cin >> l;
	rng::sort(T);
	rng::sort(L);
	int k = 0;
	while (!L.empty())
	{
		while (!T.empty() && T.back() > L.back())
			T.pop_back();
		if (T.empty())
			break;
		++k;
		L.pop_back();
		T.pop_back();
	}
	cout << k;
}
